
This is a resubmission.

* I have adjusted Authors and Licences to reflect the bundling of
  FreeType and Harfbuzz.

* I have notified the authors of Harfbuzz that the pedantic warning
  caused by including their C headers poses issues to get packages
  accepted in CRAN:
  <https://github.com/harfbuzz/harfbuzz/issues/504#issuecomment-396052904>


## Test environments

* local OS X install, R release
* ubuntu 12.04 (on travis-ci), R 3.2, oldrel, release and devel
* win-builder (devel and release)
* r-hub platforms


## R CMD check results

0 errors | 1 warning | 0 notes

The following warning occurs when compiling with `-pedantic`:

```
Found the following significant warnings during compilation:
ISO C restricts enumerator values to range of 'int' [-Wpedantic]
```

This warning comes from including the harfbuzz C headers. See
discussion on their mailing list:

<https://lists.freedesktop.org/archives/harfbuzz/2014-March/004150.html>


## Reverse dependencies

N/A
