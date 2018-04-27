#define R_NO_REMAP
#include <Rinternals.h>

#include <ft2build.h>
#include FT_FREETYPE_H

// Explicit semantics
#define ft_library FT_LibraryRec_
#define ft_face FT_FaceRec_

#include <hb.h>
#include <hb-ft.h>

#include "string-info.h"


int compute_string_width(const char* string,
                         const char* font_path,
                         int font_size,
                         double* string_width,
                         struct typographical_metrics* metrics) {
  int error = 0;

  struct ft_library* library;
  if ((error = FT_Init_FreeType(&library))) {
    goto no_cleanup;
  }
  struct ft_face* face;
  if ((error = FT_New_Face(library, font_path, 0, &face))) {
    goto ft_library_cleanup;
  }

  int size_26_6 = font_size * 64;
  FT_Set_Char_Size(face, 0, size_26_6, 0, 0);

  hb_font_t* font = hb_ft_font_create(face, NULL);
  if (!font) {
    error = 1;
    goto ft_face_cleanup;
  }
  hb_buffer_t* buffer = hb_buffer_create();
  if (!buffer) {
    error = 1;
    goto hb_font_cleanup;
  }

  hb_buffer_add_utf8(buffer, string, strlen(string), 0, strlen(string));
  hb_buffer_guess_segment_properties(buffer);
  hb_buffer_set_direction(buffer, HB_DIRECTION_LTR);

  hb_shape(font, buffer, NULL, 0);

  size_t len = hb_buffer_get_length(buffer);
  hb_glyph_position_t* pos = hb_buffer_get_glyph_positions(buffer, NULL);

  *string_width = 0.0;
  for (size_t i = 0; i < len; i++) {
    *string_width += pos[i].x_advance / 64.0;
  }

  if (metrics) {
    hb_font_extents_t hb_extents;
    hb_font_get_extents_for_direction(font, HB_DIRECTION_LTR, &hb_extents);
    metrics->ascender = hb_extents.ascender / 64.0;
    metrics->descender = -hb_extents.descender / 64.0;
    metrics->linegap = hb_extents.line_gap / 64.0;
  }

  hb_buffer_destroy(buffer);
 hb_font_cleanup:
  hb_font_destroy(font);
 ft_face_cleanup:
  FT_Done_Face(face);
 ft_library_cleanup:
  FT_Done_FreeType(library);
 no_cleanup:
  return error;
}

const char* metrics_names[] = {
  "width", "ascender", "descender", "linegap", ""
};

validate_string_info_inputs(SEXP* string, SEXP* font_size, SEXP* font_file) {
  int n_protect = 0;

  if (TYPEOF(*string) != STRSXP || Rf_length(*string) != 1) {
    Rf_errorcall(R_NilValue, "`string` must be a length 1 character vector");
  }
  if (TYPEOF(*font_file) != STRSXP || Rf_length(*font_file) != 1) {
    Rf_errorcall(R_NilValue, "`font_file` must be a length 1 character vector");
  }

  if (TYPEOF(*font_size) == REALSXP) {
    *font_size = PROTECT(Rf_coerceVector(*font_size, INTSXP));
    ++n_protect;
  }
  if (TYPEOF(*font_size) != INTSXP || Rf_length(*font_size) != 1) {
    Rf_errorcall(R_NilValue, "`font_size` must be a length 1 numeric vector");
  }
  return n_protect;
}

SEXP string_info(SEXP string, SEXP font_size, SEXP font_file) {
  int n_protect = validate_string_info_inputs(&string, &font_size, &font_file);

  const char* text = Rf_translateCharUTF8(STRING_ELT(string, 0));
  const char* font_path = CHAR(STRING_ELT(font_file, 0));
  int size = INTEGER(font_size)[0];

  struct typographical_metrics metrics = { 0.0, 0.0, 0.0 };

  SEXP info = PROTECT(Rf_mkNamed(REALSXP, metrics_names));
  ++n_protect;
  double* info_ptr = REAL(info);

  if (compute_string_width(text, font_path, size, info_ptr, &metrics)) {
    Rf_errorcall(R_NilValue, "Couldn't compute textbox metrics");
  }

  *(++info_ptr) = metrics.ascender;
  *(++info_ptr) = metrics.descender;
  *(++info_ptr) = metrics.linegap;

  UNPROTECT(n_protect);
  return info;
}

SEXP string_width(SEXP string, SEXP font_size, SEXP font_file) {
  int n_protect = validate_string_info_inputs(&string, &font_size, &font_file);

  const char* text = Rf_translateCharUTF8(STRING_ELT(string, 0));
  const char* font_path = CHAR(STRING_ELT(font_file, 0));
  int size = INTEGER(font_size)[0];

  SEXP info = PROTECT(Rf_allocVector(REALSXP, 1));
  ++n_protect;
  double* info_ptr = REAL(info);

  if (compute_string_width(text, font_path, size, info_ptr, NULL)) {
    Rf_errorcall(R_NilValue, "Couldn't compute textbox metrics");
  }

  UNPROTECT(n_protect);
  return info;
}
