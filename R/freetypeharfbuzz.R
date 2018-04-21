#' @useDynLib freetypeharfbuzz, .registration = TRUE
NULL

string_width <- function(x, font = NULL) {
  if (is.null(font)) {
    font <- fontquiver::font("Liberation", "sans", "regular")$ttf
  }
  .Call(freetype_width_ptr, x, font)
}
