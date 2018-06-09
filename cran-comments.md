
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

It seems best to ignore this warning.


## Reverse dependencies

N/A
