#!/bin/sh -e

SCRIPT=$(readlink -f "$0")
BASEDIR=$(dirname "$SCRIPT")
BUILDDIR="$BASEDIR/build"

if test -d ${BUILDDIR}; then
	rm -rf ${BUILDDIR}
fi

mkdir ${BUILDDIR}

echo "entering ${BUILDDIR}"
cd ${BUILDDIR}

cmake ..
make

echo "entering ${BASEDIR}"
cd ${BASEDIR}
