#' @useDynLib freetypeharfbuzz, .registration = TRUE
NULL

string_info <- function(string, font_size = 12, font_file = NULL) {
  if (is.null(font_file)) {
    font_file <- fontquiver::font("Liberation", "sans", "regular")$ttf
  }
  .Call(freetypeharfbuzz_string_info, string, font_size, font_file)
}
