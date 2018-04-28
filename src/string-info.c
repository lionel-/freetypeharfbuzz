#include "harfbuzz.h"
#include "string-info.h"


int calc_string_width(const char* string,
                      const char* font_path,
                      double font_size,
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

int calc_string_info(const char* string,
                     const char* font_path,
                     double font_size,
                     struct string_metrics* metrics_out) {
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
  hb_glyph_info_t* info = hb_buffer_get_glyph_infos(buffer, NULL);

  hb_position_t width = 0;
  hb_position_t ascent = 0;
  hb_position_t descent = 0;

  for (size_t i = 0; i < len; i++) {
    width += pos[i].x_advance;

    hb_glyph_extents_t extents;
    hb_font_get_glyph_extents(font, info[i].codepoint, &extents);

    hb_position_t pos_y_bearing = extents.y_bearing;
    hb_position_t pos_height = -extents.height;
    hb_position_t pos_ascent;
    hb_position_t pos_descent;
    if (pos_y_bearing < 0) {
      pos_ascent = 0;
      pos_descent = -pos_y_bearing + pos_height;
    } else {
      pos_ascent = pos_y_bearing;
      pos_descent = pos_y_bearing - pos_height;
      pos_descent = pos_descent >= 0 ? 0 : -pos_descent;
    }

    if (pos_ascent > ascent) {
      ascent = pos_ascent;
    }
    if (pos_descent > descent) {
      descent = pos_descent;
    }
  }

  metrics_out->width = width / 64.0;
  metrics_out->ascent = ascent / 64.0;
  metrics_out->descent = descent / 64.0;
  metrics_out->height = (ascent + descent) / 64.0;

  hb_buffer_destroy(buffer);
 hb_font_cleanup:
  hb_font_destroy(font);
 no_cleanup:
  return error;
}
