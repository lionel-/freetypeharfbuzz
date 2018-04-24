#!/usr/bin/env sh

if [ -z $1 ]; then
    echo "No archive file supplied"
    exit 1
fi


if command -v gtar; then
    TAR=gtar
else
    TAR=tar
fi

${TAR} -xf $1
