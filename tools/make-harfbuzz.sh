#!/usr/bin/env sh
set -e

if [ -z $HB_VERSION ]; then
    HB_VERSION=1.7.6
fi

HB="harfbuzz-${HB_VERSION}"
HB_ARCHIVE="downloads/${HB}.tar.bz2"

if [ ! -e ${HB_ARCHIVE} ]; then
    echo "Please run 'make ${HB_ARCHIVE}'"
    exit 1
fi


bunzip2 < ${HB_ARCHIVE} | tar xf -

# Use gpatch because Solaris 10 `patch` does not support modern diffs.
# The patch ensures the configure script detects FreeType as R-hub has
# a very old version of pkg-config that does not seem to work with
# modern .pc files.
if [ $(uname) = "SunOS" ]; then
    (cd ${HB}; gpatch < ../harfbuzz-pkgconfig.diff)
fi

tar cf - ${HB} | gzip -9 > ${HB}.tar.gz
rm -rf ${HB}
