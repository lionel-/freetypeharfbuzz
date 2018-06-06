#include "harfbuzz.h"
#include "font-info.h"


int get_font_info(const char* font_path,
                  double font_size,
                  struct font_metrics* metrics_out) {
  int error = 0;;

  if (!metrics_out) {
    error = 1;
    goto no_cleanup;
  }

  hb_font_t* font;
  if ((error = init_font(font_path, font_size, &font))) {
    goto no_cleanup;
  }

  hb_font_extents_t hb_extents;
  hb_font_get_extents_for_direction(font, HB_DIRECTION_LTR, &hb_extents);

  metrics_out->ascent = hb_extents.ascender / 64.0;
  metrics_out->descent = -hb_extents.descender / 64.0;
  metrics_out->linegap = hb_extents.line_gap / 64.0;

  hb_font_destroy(font);
 no_cleanup:
  return error;
}
