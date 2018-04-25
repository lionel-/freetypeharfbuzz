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
