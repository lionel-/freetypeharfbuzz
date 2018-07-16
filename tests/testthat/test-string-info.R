context("string-info")

test_that("width", {
  expect_identical(rounded_width("foobar"), 34.0156)
  expect_identical(rounded_width("o."), 10.000)
  expect_identical(rounded_width("."), 3.3281)
})

test_that("extents takes kerning into account", {
  expect_identical(rounded_width("VA"), 15.1094)
  combined <- rounded_width("VA")
  separate1 <- rounded_width("V")
  separate2 <- rounded_width("V")
  expect_true(combined < separate1 + separate2)
})

test_that("inputs are type-checked", {
  expect_error(str_info("foo", font_file = letters), "must be a length 1 character")
  expect_error(str_info(globalenv(), font_file = "foo"), "must be a length 1 character")
  expect_error(str_info("foo", font_size = "bar"), "must be a length 1 numeric")
  expect_error(str_info("foo", font_size = 1:3), "must be a length 1 numeric")
})

test_that("can supply integer or double size", {
  expect_identical(str_info("foo", 12), str_info("foo", 12L))
})

test_that("can retrieve typographical metrics", {
  expect_identical(font_info(11), c(ascent = 10, descent = 3, linegap = 0))
  expect_identical(font_info(12), c(ascent = 11, descent = 3, linegap = 0))
  expect_identical(font_info(13), c(ascent = 12, descent = 3, linegap = 0))

  font <- fontquiver::font("Bitstream Vera", "sans", "roman")$ttf
  expect_identical(font_info(11, font), c(ascent = 11, descent = 3, linegap = -1))
  expect_identical(font_info(12, font), c(ascent = 12, descent = 3, linegap = -1))
  expect_identical(font_info(13, font), c(ascent = 13, descent = 4, linegap = -2))
})

test_that("size is taken into account", {
  ascender_11 <- font_info(11)[["ascent"]]
  ascender_12 <- font_info(12)[["ascent"]]
  expect_true(ascender_11 < ascender_12)
})

test_that("typographical height is monotonically increasing", {
  gaps <- vapply(1:50, function(size) sum(font_info(size)), double(1))
  expect_true(all(gaps == cummax(gaps)))
})

test_that("string metrics are computed for various edge cases", {
  # metrics:          width   height  ascent  descent
  expect_metrics(".", 3.3281, 1.2812, 1.2812, 0.0000)
  expect_metrics("^", 5.6250, 8.2500, 8.2500, 0.0000)
  expect_metrics("ô", 6.6719, 8.8594, 8.7344, 0.1250)
  expect_metrics("˛", 4.0000, 2.5000, 0.0000, 2.5000)
  expect_metrics("̣", 0.0000, 1.8281, 0.0000, 1.8281)
  expect_metrics("ç", 6.0000, 9.0000, 6.4531, 2.5469)
  expect_metrics("c", 6.0000, 6.5781, 6.4531, 0.1250)
  expect_metrics("ͅ",  0.0000, 2.4844, 0.0000, 2.4844)
  expect_metrics("͞", 0.0000, 8.4219, 8.4219, 0.0000)
})

test_that("supports fractional font sizes", {
  widths <- c(
    str_width("foo", 12),
    str_width("foo", 12.1),
    str_width("foo", 12.2)
  )
  expect_true(all(widths == cummax(widths)))
})
