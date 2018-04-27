#include "harfbuzz.h"
#include "string-info.h"

int compute_string_width(const char* string,
                         const char* font_path,
                         int font_size,
                         double* string_width) {
  int error = 0;;
  hb_font_t* font;

  if ((error = init_font(font_path, font_size, &font))) {
    goto no_cleanup;
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

  hb_buffer_destroy(buffer);
 hb_font_cleanup:
  hb_font_destroy(font);
 no_cleanup:
  return error;
}
