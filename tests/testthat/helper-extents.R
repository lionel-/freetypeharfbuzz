
rounded_width <- function(text) {
  round(str_width(text), 4)
}

expect_metrics <- function(string, w, h, a, d) {
  metrics <- round(str_info(string), 4)
  expect_equal(metrics, c(width = w, height = h, ascent = a, descent = d))
}
