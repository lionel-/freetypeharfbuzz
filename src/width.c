#define R_NO_REMAP
#include <Rinternals.h>

#include <ft2build.h>
#include FT_FREETYPE_H


SEXP freetype_width(SEXP str, SEXP font) {
  FT_Library library;
  FT_Face face;
  int error;

  error = FT_Init_FreeType(&library);
  if (error) {
    Rf_error("FT init error");
  }

  const char* font_path = CHAR(STRING_ELT(font, 0));
  error = FT_New_Face(library, font_path, 0, &face );
  if (error) {
    Rf_error("FT face error");
  }

  int size_pt = 12 * 64;
  int height = 300;
  int width = 300;
  FT_Set_Char_Size(face, 0, size_pt, width, height);

  return R_NilValue;
}
