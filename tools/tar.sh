#!/usr/bin/env sh

if [ -z $1 ]; then
    echo "No target file supplied"
    exit 1
fi
if [ -z $1 ]; then
    echo "No source path supplied"
    exit 1
fi
if [ -z $3 ]; then
    COMPR="'none'"
else
    COMPR="'$3'"
fi


if [ -z ${R_HOME} ]; then
    R=R;
else
    R="${R_HOME}/bin/R"
fi

echo "suppressWarnings(tar('${1}', '${2}', compression = ${COMPR}))" | ${R} --vanilla --slave
