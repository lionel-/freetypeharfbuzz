#ifndef FREETYPEHARFBUZZ_FONT_INFO_H
#define FREETYPEHARFBUZZ_FONT_INFO_H


struct font_metrics {
  double ascent;
  double descent;
  double linegap;
};

int get_font_info(const char* font_path,
                  int font_size,
                  struct font_metrics* metrics);


#endif
