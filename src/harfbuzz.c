#include "freetype.h"
#include "harfbuzz.h"

int init_font(const char* font_path,
              int font_size,
              hb_font_t** font) {
  int error = 0;

  struct ft_face* face;
  if ((error = FT_New_Face(library, font_path, 0, &face))) {
    goto no_cleanup;
  }

  int size_26_6 = font_size * 64;
  FT_Set_Char_Size(face, 0, size_26_6, 0, 0);

  *font = hb_ft_font_create(face, NULL);
  if (!*font) {
    error = 1;
    goto ft_face_cleanup;
  }

  return 0;

 ft_face_cleanup:
  FT_Done_Face(face);
 no_cleanup:
  return error;
}
