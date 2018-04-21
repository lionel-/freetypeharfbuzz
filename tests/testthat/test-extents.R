context("extents")

test_that("extents", {
  extents <- round(string_width("foobar"), 4)
  expect_identical(extents, c(141.7969, 0.000))
})
