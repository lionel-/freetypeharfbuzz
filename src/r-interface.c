#define R_NO_REMAP
#include <Rinternals.h>

#include "string-info.h"
#include "font-info.h"


int validate_string_info_inputs(SEXP* string, SEXP* font_size, SEXP* font_file) {
  int n_protect = 0;

  if (string) {
    if (TYPEOF(*string) != STRSXP || Rf_length(*string) != 1) {
      Rf_errorcall(R_NilValue, "`string` must be a length 1 character vector");
    }
  }
  if (TYPEOF(*font_file) != STRSXP || Rf_length(*font_file) != 1) {
    Rf_errorcall(R_NilValue, "`font_file` must be a length 1 character vector");
  }

  if (TYPEOF(*font_size) == INTSXP) {
    *font_size = PROTECT(Rf_coerceVector(*font_size, REALSXP));
    ++n_protect;
  }
  if (TYPEOF(*font_size) != REALSXP || Rf_length(*font_size) != 1) {
    Rf_errorcall(R_NilValue, "`font_size` must be a length 1 numeric vector");
  }
  return n_protect;
}

const char* string_info_names[] = {
  "width", "height", "ascent", "descent", ""
};

SEXP string_info(SEXP string, SEXP font_size, SEXP font_file) {
  int n_protect = validate_string_info_inputs(&string, &font_size, &font_file);

  const char* text = Rf_translateCharUTF8(STRING_ELT(string, 0));
  const char* font_path = CHAR(STRING_ELT(font_file, 0));
  double size = REAL(font_size)[0];

  struct string_metrics metrics;
  if (calc_string_info(text, font_path, size, &metrics)) {
    Rf_errorcall(R_NilValue, "Couldn't compute textbox metrics");
  }

  SEXP info = PROTECT(Rf_mkNamed(REALSXP, string_info_names));
  ++n_protect;
  double* info_ptr = REAL(info);

  *info_ptr = metrics.width;
  *(++info_ptr) = metrics.height;
  *(++info_ptr) = metrics.ascent;
  *(++info_ptr) = metrics.descent;

  UNPROTECT(n_protect);
  return info;
}

SEXP string_width(SEXP string, SEXP font_size, SEXP font_file) {
  int n_protect = validate_string_info_inputs(&string, &font_size, &font_file);

  const char* text = Rf_translateCharUTF8(STRING_ELT(string, 0));
  const char* font_path = CHAR(STRING_ELT(font_file, 0));
  double size = REAL(font_size)[0];

  SEXP info = PROTECT(Rf_allocVector(REALSXP, 1));
  ++n_protect;
  double* info_ptr = REAL(info);

  if (calc_string_width(text, font_path, size, info_ptr)) {
    Rf_errorcall(R_NilValue, "Couldn't compute textbox metrics");
  }

  UNPROTECT(n_protect);
  return info;
}

const char* font_info_names[] = {
  "ascent", "descent", "linegap", ""
};

SEXP font_info(SEXP font_size, SEXP font_file) {
  int n_protect = validate_string_info_inputs(NULL, &font_size, &font_file);

  const char* font_path = CHAR(STRING_ELT(font_file, 0));
  double size = REAL(font_size)[0];

  struct font_metrics metrics = { 0.0, 0.0, 0.0 };

  if (get_font_info(font_path, size, &metrics)) {
    Rf_errorcall(R_NilValue, "Couldn't compute textbox metrics");
  }

  SEXP info = Rf_mkNamed(REALSXP, font_info_names);
  double* info_ptr = REAL(info);

  *info_ptr = metrics.ascent;
  *(++info_ptr) = metrics.descent;
  *(++info_ptr) = metrics.linegap;

  UNPROTECT(n_protect);
  return info;
}
