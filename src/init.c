#include <R.h>
#include <Rinternals.h>
#include <stdlib.h> // for NULL
#include <R_ext/Rdynload.h>

extern SEXP freetype_width(SEXP, SEXP);

static const R_CallMethodDef CallEntries[] = {
    {"freetype_width_ptr",  (DL_FUNC) &freetype_width,  2},
    {NULL, NULL, 0}
};

void R_init_freetypeharfbuzz(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
