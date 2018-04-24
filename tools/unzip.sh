#!/usr/bin/env sh

if [ -z $1 ]; then
    echo "No target file supplied"
    exit 1
fi
if [ ! -z $2 ]; then
    EXDIR="'$2'"
fi


if [ -z ${R_HOME} ]; then
    R=R;
else
    R="${R_HOME}/bin/R"
fi

echo "unzip('$1', exdir = ${EXDIR}, unzip = 'internal')" | ${R} --vanilla --slave
