#' @useDynLib freetypeharfbuzz, .registration = TRUE
NULL

.onLoad <- function(lib, pkg) {
  .Call(freetypeharfbuzz_library_load)
}
.onUnLoad <- function(lib, pkg) {
  .Call(freetypeharfbuzz_library_unload)
}

#' Font metrics
#'
#' @description
#'
#' * `font_info()` returns the typographical metrics (ascent, descent,
#'    linegap) for a font.
#'
#' * `str_info()` returns the metrics (width, height, ascent,
#'   descent) for a string. `str_width()` only returns the width.
#'
#' @param font_size Font size in point.
#' @param font_file Path to a ttf or otf file.
#' @param string A string whose metrics will be computed.
#'
#' @export
#' @examples
#' file <- fontquiver::font("Liberation", "serif", "bold")$ttf
#' font_info(font_size = 13, font_file = file)
#'
#' str_width("foobar", font_size = 13)
#' str_info("foobar", font_size = 13)
#' str_info("foobar", font_size = 13, font_file = file)
font_info <- function(font_size = 12, font_file = NULL) {
  if (is.null(font_file)) {
    font_file <- fontquiver::font("Liberation", "sans", "regular")$ttf
  }
  .Call(freetypeharfbuzz_font_info, font_size, font_file)
}

#' @rdname font_info
#' @export
str_info <- function(string, font_size = 12, font_file = NULL) {
  if (is.null(font_file)) {
    font_file <- fontquiver::font("Liberation", "sans", "regular")$ttf
  }
  .Call(freetypeharfbuzz_string_info, string, font_size, font_file)
}

#' @rdname font_info
#' @export
str_width <- function(string, font_size = 12, font_file = NULL) {
  if (is.null(font_file)) {
    font_file <- fontquiver::font("Liberation", "sans", "regular")$ttf
  }
  .Call(freetypeharfbuzz_string_width, string, font_size, font_file)
}
