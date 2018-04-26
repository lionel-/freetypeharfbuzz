
rounded_width <- function(text) {
  round(text_extents(text), 4)[["width"]]
}
