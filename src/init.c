#include <R.h>
#include <Rinternals.h>
#include <stdlib.h> // for NULL
#include <R_ext/Rdynload.h>

SEXP library_load();
SEXP library_unload();

extern SEXP string_info(SEXP, SEXP, SEXP);
extern SEXP string_width(SEXP, SEXP, SEXP);

static const R_CallMethodDef CallEntries[] = {
    {"freetypeharfbuzz_library_load", (DL_FUNC) &library_load, 0},
    {"freetypeharfbuzz_library_unload", (DL_FUNC) &library_unload, 0},
    {"freetypeharfbuzz_string_info", (DL_FUNC) &string_info, 3},
    {"freetypeharfbuzz_string_width", (DL_FUNC) &string_width, 3},
    {NULL, NULL, 0}
};


#include "string-info.h"

void R_init_freetypeharfbuzz(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);

    R_RegisterCCallable("freetypeharfbuzz", "freetypeharfbuzz_compute_string_width", (DL_FUNC) &compute_string_width);
}


#include "freetype.h"

SEXP library_load() {
  if (FT_Init_FreeType(&library)) {
    Rf_errorcall(R_NilValue, "Can't initialise FreeType library");
  }
  return R_NilValue;
}
SEXP library_unload() {
  FT_Done_FreeType(library);
  return R_NilValue;
}
