#' @useDynLib freetypeharfbuzz, .registration = TRUE
NULL

.onLoad <- function(lib, pkg) {
  .Call(freetypeharfbuzz_library_load)
}
.onUnLoad <- function(lib, pkg) {
  .Call(freetypeharfbuzz_library_unload)
}

string_info <- function(string, font_size = 12, font_file = NULL) {
  if (is.null(font_file)) {
    font_file <- fontquiver::font("Liberation", "sans", "regular")$ttf
  }
  .Call(freetypeharfbuzz_string_info, string, font_size, font_file)
}

string_width <- function(string, font_size = 12, font_file = NULL) {
  if (is.null(font_file)) {
    font_file <- fontquiver::font("Liberation", "sans", "regular")$ttf
  }
  .Call(freetypeharfbuzz_string_width, string, font_size, font_file)
}
