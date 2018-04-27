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
  expect_error(string_info("foo", font_file = letters), "must be a length 1 character")
  expect_error(string_info(globalenv(), font_file = "foo"), "must be a length 1 character")
  expect_error(string_info("foo", font_size = "bar"), "must be a length 1 numeric")
  expect_error(string_info("foo", font_size = 1:3), "must be a length 1 numeric")
})

test_that("can supply integer or double size", {
  expect_identical(string_info("foo", 12), string_info("foo", 12L))
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
