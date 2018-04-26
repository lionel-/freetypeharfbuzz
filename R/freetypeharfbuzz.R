#' @useDynLib freetypeharfbuzz, .registration = TRUE
NULL

text_extents <- function(string, font_size = 12, font_file = NULL) {
  if (is.null(font_file)) {
    font_file <- fontquiver::font("Liberation", "sans", "regular")$ttf
  }
  .Call(freetypeharfbuzz_text_extents, string, font_size, font_file)
}
