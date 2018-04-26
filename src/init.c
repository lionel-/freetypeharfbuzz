#include <R.h>
#include <Rinternals.h>
#include <stdlib.h> // for NULL
#include <R_ext/Rdynload.h>

extern SEXP string_info(SEXP, SEXP, SEXP);
extern SEXP string_width(SEXP, SEXP, SEXP);

static const R_CallMethodDef CallEntries[] = {
    {"freetypeharfbuzz_string_info",  (DL_FUNC) &string_info,  3},
    {"freetypeharfbuzz_string_width",  (DL_FUNC) &string_width,  3},
    {NULL, NULL, 0}
};


#include "string-info.h"

void R_init_freetypeharfbuzz(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);

    R_RegisterCCallable("freetypeharfbuzz", "freetypeharfbuzz_compute_string_width", (DL_FUNC) &compute_string_width);
}
