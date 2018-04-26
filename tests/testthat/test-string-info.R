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

test_that("size is taken into account", {
  ascender_11 <- string_info("foo", 11)[["ascender"]]
  ascender_12 <- string_info("foo", 12)[["ascender"]]
  expect_true(ascender_11 < ascender_12)
})
