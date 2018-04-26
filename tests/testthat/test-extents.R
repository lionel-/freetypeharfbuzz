context("extents")

test_that("extents", {
  expect_identical(rounded_extents("foobar"), c(34.0156, 9.000))
  expect_identical(rounded_extents("o."), c(10.000, 7.000))
  expect_identical(rounded_extents("."), c(3.3281, 1.000))
})

test_that("extents takes kerning into account", {
  expect_identical(rounded_extents("VA"), c(15.1094, 9.000))
  combined <- rounded_extents("VA")[[1]]
  separate1 <- rounded_extents("V")[[1]]
  separate2 <- rounded_extents("V")[[1]]
  expect_true(combined < separate1 + separate2)
})

test_that("inputs are type-checked", {
  expect_error(text_extents("foo", font_file = letters), "must be a length 1 character")
  expect_error(text_extents(globalenv(), font_file = "foo"), "must be a length 1 character")
  expect_error(text_extents("foo", font_size = "bar"), "must be a length 1 numeric")
  expect_error(text_extents("foo", font_size = 1:3), "must be a length 1 numeric")
})

test_that("can supply integer or double size", {
  expect_identical(text_extents("foo", 12), text_extents("foo", 12L))
})

test_that("size is taken into account", {
  height_11 <- text_extents("foo", 11)[[2]]
  height_12 <- text_extents("foo", 12)[[2]]
  expect_true(height_11 < height_12)
})
