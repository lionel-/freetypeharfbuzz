#ifndef FREETYPEHARFBUZZ_STRING_INFO_H
#define FREETYPEHARFBUZZ_STRING_INFO_H


struct typographical_metrics {
  double ascender;
  double descender;
  double linegap;
};

int compute_string_width(const char*,
                         const char*,
                         int,
                         double*,
                         struct typographical_metrics*);


#endif
