#ifndef FREETYPEHARFBUZZ_STRING_INFO_H
#define FREETYPEHARFBUZZ_STRING_INFO_H


struct string_metrics {
  double width;
  double height;
  double ascent;
  double descent;
};

int calc_string_width(const char* string,
                      const char* font_path,
                      int font_size,
                      double* metrics);

int calc_string_info(const char* string,
                     const char* font_path,
                     int font_size,
                     struct string_metrics* metrics);


#endif
