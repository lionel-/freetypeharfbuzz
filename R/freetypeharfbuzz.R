#' @useDynLib freetypeharfbuzz, .registration = TRUE
NULL

text_extents <- function(x, font = NULL) {
  if (is.null(font)) {
    font <- fontquiver::font("Liberation", "sans", "regular")$ttf
  }
  .Call(freetypeharfbuzz_text_extents, x, font)
}
