#define R_NO_REMAP
#include <Rinternals.h>

#include <ft2build.h>
#include FT_FREETYPE_H

// Explicit semantics
#define ft_library FT_LibraryRec_
#define ft_face FT_FaceRec_
#define ft_slot FT_GlyphSlotRec

#include <hb.h>
#include <hb-ft.h>

#include <math.h>

char* utf8_next_char(const char* str);


struct extents {
  double width;
  double height;
};

int compute_text_width(const char* text, struct ft_face* face,
                       struct extents* extents) {
  int error = 0;

  hb_font_t* font = hb_ft_font_create(face, NULL);
  if (!font) {
    error = 1;
    goto no_cleanup;
  }
  hb_buffer_t* buffer = hb_buffer_create();
  if (!buffer) {
    error = 1;
    goto hb_font_cleanup;
  }

  hb_buffer_add_utf8(buffer, text, strlen(text), 0, strlen(text));
  hb_buffer_guess_segment_properties(buffer);
  hb_buffer_set_direction(buffer, HB_DIRECTION_LTR);

  hb_shape(font, buffer, NULL, 0);

  size_t len = hb_buffer_get_length(buffer);
  hb_glyph_position_t* pos = hb_buffer_get_glyph_positions(buffer, NULL);

  for (size_t i = 0; i < len; i++) {
    extents->width += pos[i].x_advance / 64.0;
  }

  hb_buffer_destroy(buffer);
 hb_font_cleanup:
  hb_font_destroy(font);
 no_cleanup:
  return error;
}

int compute_text_height(const char* text, struct ft_face* face,
                        struct extents* extents) {
  FT_Pos max_ascent = 0;
  FT_Pos max_descent = 0;

  const char* str = text;
  while (*str) {
    FT_Load_Char(face, *str, FT_LOAD_DEFAULT);
    FT_Glyph_Metrics metrics = face->glyph->metrics;

    FT_Pos ascent = metrics.horiBearingY;
    if (ascent > max_ascent) {
      max_ascent = ascent;
    }

    FT_Pos descent = metrics.height - ascent;
    if (descent > max_descent) {
      max_descent = descent;
    }

    str = utf8_next_char(str);
  }

  extents->height = (max_ascent + max_descent) / 64.0;
  return 0;
}

int compute_text_extents(const char* text, const char* font_path,
                         int size, struct extents* extents) {
  int error = 0;

  struct ft_library* library;
  if ((error = FT_Init_FreeType(&library))) {
    goto no_cleanup;
  }
  struct ft_face* face;
  if ((error = FT_New_Face(library, font_path, 0, &face))) {
    goto ft_library_cleanup;
  }

  int size_pt = size * 64;
  FT_Set_Char_Size(face, 0, size_pt, 72, 72);

  error = compute_text_width(text, face, extents);
  error = compute_text_height(text, face, extents);

  FT_Done_Face(face);
 ft_library_cleanup:
  FT_Done_FreeType(library);
 no_cleanup:
  return error;
}

SEXP text_extents(SEXP text_input, SEXP font_input) {
  const char* text = Rf_translateCharUTF8(STRING_ELT(text_input, 0));
  const char* font_path = CHAR(STRING_ELT(font_input, 0));

  struct extents extents = { 0, 0 };
  if (compute_text_extents(text, font_path, 12, &extents)) {
    Rf_errorcall(R_NilValue, "Couldn't compute textbox extents");
  }

  SEXP out = Rf_allocVector(REALSXP, 2);
  REAL(out)[0] = extents.width;
  REAL(out)[1] = extents.height;
  return out;
}
