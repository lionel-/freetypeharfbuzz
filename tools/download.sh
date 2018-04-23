#!/usr/bin/env sh

if [ -z $1 ]; then
    echo "No URL supplied"
    exit 1
fi
if [ -z $2 ]; then
    echo "No target file supplied"
    exit 1
fi

if [ -z ${R_HOME} ]; then
    R=R
else
    R="${R_HOME}/bin/R"
fi

echo "download.file('$1', '$2', mode = 'wb')" | ${R} --vanilla --slave
