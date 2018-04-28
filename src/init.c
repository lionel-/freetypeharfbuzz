#include <R.h>
#include <Rinternals.h>
#include <stdlib.h> // for NULL
#include <R_ext/Rdynload.h>

SEXP library_load();
SEXP library_unload();

extern SEXP font_info(SEXP, SEXP);
extern SEXP string_info(SEXP, SEXP, SEXP);
extern SEXP string_width(SEXP, SEXP, SEXP);

static const R_CallMethodDef CallEntries[] = {
    { "freetypeharfbuzz_font_info",      (DL_FUNC) &font_info,      2 },
    { "freetypeharfbuzz_library_load",   (DL_FUNC) &library_load,   0 },
    { "freetypeharfbuzz_library_unload", (DL_FUNC) &library_unload, 0 },
    { "freetypeharfbuzz_string_info",    (DL_FUNC) &string_info,    3 },
    { "freetypeharfbuzz_string_width",   (DL_FUNC) &string_width,   3 },
    { NULL, NULL, 0 }
};


#include "font-info.h"
#include "string-info.h"

void R_init_freetypeharfbuzz(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);

    R_RegisterCCallable("freetypeharfbuzz", "fthb_calc_string_info",  (DL_FUNC) &calc_string_info);
    R_RegisterCCallable("freetypeharfbuzz", "fthb_calc_string_width", (DL_FUNC) &calc_string_width);
    R_RegisterCCallable("freetypeharfbuzz", "fthb_get_font_info",     (DL_FUNC) &get_font_info);
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
