#include "freetype.h"
#include "harfbuzz.h"

void ft_destroy_face(void* data) {
  struct ft_face* face = (struct ft_face*) data;
  FT_Done_Face(face);
}

int init_font(const char* font_path,
              double font_size,
              hb_font_t** font_out) {
  int error = 0;

  struct ft_face* face;
  if ((error = FT_New_Face(library, font_path, 0, &face))) {
    goto no_cleanup;
  }

  FT_F26Dot6 size_26_6 = font_size * 64;
  FT_Set_Char_Size(face, 0, size_26_6, 0, 0);

  hb_font_t* font = hb_ft_font_create(face, &ft_destroy_face);
  if (!font) {
    error = 1;
    goto ft_face_cleanup;
  }

  *font_out = font;
  return 0;

 ft_face_cleanup:
  FT_Done_Face(face);
 no_cleanup:
  return error;
}

int init_buffer(const char* string,
                hb_font_t* font,
                hb_buffer_t** buffer_out) {
  hb_buffer_t* buffer = hb_buffer_create();
  if (!buffer) {
    return 1;
  }

  hb_buffer_add_utf8(buffer, string, strlen(string), 0, strlen(string));
  hb_buffer_guess_segment_properties(buffer);
  hb_buffer_set_direction(buffer, HB_DIRECTION_LTR);

  hb_shape(font, buffer, NULL, 0);

  *buffer_out = buffer;
  return 0;
}
