#define R_NO_REMAP
#include <Rinternals.h>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <hb.h>
#include <hb-ft.h>


SEXP freetype_width(SEXP str, SEXP str_font) {
  FT_Library library;
  FT_Face face;
  int error;

  error = FT_Init_FreeType(&library);
  if (error) {
    Rf_error("FT init error");
  }

  const char* font_path = CHAR(STRING_ELT(str_font, 0));
  error = FT_New_Face(library, font_path, 0, &face );
  if (error) {
    Rf_error("FT face error");
  }

  int size_pt = 12 * 64;
  int height = 300;
  int width = 300;
  FT_Set_Char_Size(face, 0, size_pt, width, height);


  const char* text = CHAR(STRING_ELT(str, 0));

  hb_buffer_t* buf;
  buf = hb_buffer_create();
  hb_buffer_add_utf8(buf, text, strlen(text), 0, strlen(text));
  hb_buffer_guess_segment_properties(buf);

  hb_font_t* font = hb_ft_font_create(face, NULL);
  hb_shape(font, buf, NULL, 0);

  unsigned int len = hb_buffer_get_length (buf);
  hb_glyph_info_t *info = hb_buffer_get_glyph_infos (buf, NULL);
  hb_glyph_position_t *pos = hb_buffer_get_glyph_positions (buf, NULL);

  SEXP out = PROTECT(Rf_allocVector(REALSXP, 2));

  {
    double current_x = 0;
    double current_y = 0;
    for (unsigned int i = 0; i < len; i++)
      {
        hb_codepoint_t gid   = info[i].codepoint;
        unsigned int cluster = info[i].cluster;
        double x_position = current_x + pos[i].x_offset / 64.;
        double y_position = current_y + pos[i].y_offset / 64.;


        char glyphname[32];
        hb_font_get_glyph_name(font, gid, glyphname, sizeof(glyphname));

        printf ("glyph='%s'	cluster=%d	position=(%g,%g)\n",
                glyphname, cluster, x_position, y_position);

        current_x += pos[i].x_advance / 64.;
        current_y += pos[i].y_advance / 64.;
      }

    REAL(out)[0] = current_x;
    REAL(out)[1] = current_y;
  }


  hb_buffer_destroy(buf);
  FT_Done_Face(face);
  FT_Done_FreeType(library);

  UNPROTECT(1);
  return out;
}
