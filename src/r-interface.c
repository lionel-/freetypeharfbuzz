#define R_NO_REMAP
#include <Rinternals.h>

#include "string-info.h"


const char* metrics_names[] = {
  "width", "ascender", "descender", "linegap", ""
};

int validate_string_info_inputs(SEXP* string, SEXP* font_size, SEXP* font_file) {
  int n_protect = 0;

  if (TYPEOF(*string) != STRSXP || Rf_length(*string) != 1) {
    Rf_errorcall(R_NilValue, "`string` must be a length 1 character vector");
  }
  if (TYPEOF(*font_file) != STRSXP || Rf_length(*font_file) != 1) {
    Rf_errorcall(R_NilValue, "`font_file` must be a length 1 character vector");
  }

  if (TYPEOF(*font_size) == REALSXP) {
    *font_size = PROTECT(Rf_coerceVector(*font_size, INTSXP));
    ++n_protect;
  }
  if (TYPEOF(*font_size) != INTSXP || Rf_length(*font_size) != 1) {
    Rf_errorcall(R_NilValue, "`font_size` must be a length 1 numeric vector");
  }
  return n_protect;
}

SEXP string_info(SEXP string, SEXP font_size, SEXP font_file) {
  int n_protect = validate_string_info_inputs(&string, &font_size, &font_file);

  const char* text = Rf_translateCharUTF8(STRING_ELT(string, 0));
  const char* font_path = CHAR(STRING_ELT(font_file, 0));
  int size = INTEGER(font_size)[0];

  struct typographical_metrics metrics = { 0.0, 0.0, 0.0 };

  SEXP info = PROTECT(Rf_mkNamed(REALSXP, metrics_names));
  ++n_protect;
  double* info_ptr = REAL(info);

  if (compute_string_width(text, font_path, size, info_ptr, &metrics)) {
    Rf_errorcall(R_NilValue, "Couldn't compute textbox metrics");
  }

  *(++info_ptr) = metrics.ascender;
  *(++info_ptr) = metrics.descender;
  *(++info_ptr) = metrics.linegap;

  UNPROTECT(n_protect);
  return info;
}

SEXP string_width(SEXP string, SEXP font_size, SEXP font_file) {
  int n_protect = validate_string_info_inputs(&string, &font_size, &font_file);

  const char* text = Rf_translateCharUTF8(STRING_ELT(string, 0));
  const char* font_path = CHAR(STRING_ELT(font_file, 0));
  int size = INTEGER(font_size)[0];

  SEXP info = PROTECT(Rf_allocVector(REALSXP, 1));
  ++n_protect;
  double* info_ptr = REAL(info);

  if (compute_string_width(text, font_path, size, info_ptr, NULL)) {
    Rf_errorcall(R_NilValue, "Couldn't compute textbox metrics");
  }

  UNPROTECT(n_protect);
  return info;
}
