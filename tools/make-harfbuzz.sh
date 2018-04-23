#!/usr/bin/env sh
set -e

if [ -z $HB_VERSION ]; then
    HB_VERSION=1.7.6;
fi

HB="harfbuzz-${HB_VERSION}"
HB_ARCHIVE="downloads/${HB}.tar.bz2"

if [ ! -e ${HB_ARCHIVE} ]; then
    echo "Please run 'make ${HB_ARCHIVE}'"
    exit 1;
fi


# Solaris 10 `patch` does not support modern diffs
if [ $(uname) = "SunOS" ]; then
    PATCH="gpatch";
else
    PATCH="patch";
fi

bunzip2 < ${HB_ARCHIVE} | tar xf -
cd ${HB}
${PATCH} < ../harfbuzz-pkgconfig.diff
cd ..

tar cf - ${HB} | gzip -9 > ${HB}.tar.gz
rm -rf ${HB}
