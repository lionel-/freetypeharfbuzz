context("extents")

test_that("extents", {
  extents <- round(text_extents("foobar"), 4)
  expect_identical(extents, c(34.0156, 0)) # Shouldn't be zero
})
