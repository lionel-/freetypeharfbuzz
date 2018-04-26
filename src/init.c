#include <R.h>
#include <Rinternals.h>
#include <stdlib.h> // for NULL
#include <R_ext/Rdynload.h>

extern SEXP text_extents(SEXP, SEXP, SEXP);

static const R_CallMethodDef CallEntries[] = {
    {"freetypeharfbuzz_text_extents",  (DL_FUNC) &text_extents,  3},
    {NULL, NULL, 0}
};

void R_init_freetypeharfbuzz(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
