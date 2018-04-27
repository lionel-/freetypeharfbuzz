#include "harfbuzz.h"
#include "string-info.h"


struct string_metrics {
  double width;
  double height;
  double ascent;
  double descent;
};

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

int calc_string_width(const char* string,
                      const char* font_path,
                      int font_size,
                      double* width_out) {
  int error = 0;

  hb_font_t* font;
  if ((error = init_font(font_path, font_size, &font))) {
    goto no_cleanup;
  }
  hb_buffer_t* buffer;
  if ((error = init_buffer(string, font, &buffer))) {
    goto hb_font_cleanup;
  }

  size_t len = hb_buffer_get_length(buffer);
  hb_glyph_position_t* pos = hb_buffer_get_glyph_positions(buffer, NULL);
  hb_position_t width = 0;

  for (size_t i = 0; i < len; i++) {
    width += pos[i].x_advance;
  }
  *width_out = width / 64.0;

  hb_buffer_destroy(buffer);
 hb_font_cleanup:
  hb_font_destroy(font);
 no_cleanup:
  return error;
}
