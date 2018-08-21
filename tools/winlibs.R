
VERSION <- commandArgs(TRUE)

if (!file.exists(sprintf("../windows/cairo-%s/include/cairo/cairo.h", VERSION))) {
  if (getRversion() < "3.3.0") {
    setInternet2()
  }

  url <- sprintf("https://github.com/rwinlib/cairo/archive/v%s.zip", VERSION)
  download.file(url, "lib.zip", quiet = TRUE)

  dir.create("../windows", showWarnings = FALSE)
  unzip("lib.zip", exdir = "../windows")
  unlink("lib.zip")

  unlink(sprintf("../windows/cairo-%s/include", VERSION), recursive = TRUE)
  unzip("../tools/include-windows.zip", exdir = sprintf("../windows/cairo-%s", VERSION))
}
