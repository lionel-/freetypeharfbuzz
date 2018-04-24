#!/usr/bin/env sh

if [ -z $1 ]; then
    echo "No compressed file supplied"
    exit 1
fi
if [ ! -z $2 ]; then
    COMPR="'$2'"
fi
if [ ! -z $3 ]; then
    EXDIR="'$3'"
fi


if [ -z ${R_HOME} ]; then
    R=R;
else
    R="${R_HOME}/bin/R"
fi

echo "untar('$1', compressed = ${COMPR}, exdir = ${EXDIR})" | ${R} --vanilla --slave
