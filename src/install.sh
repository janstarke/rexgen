#!/bin/sh -e

BASEDIR=$(dirname "$SCRIPT")
. ${BASEDIR}/build.sh

cd ${BUILDDIR}

cmake ..

if test $(id -u) -eq 0; then
	make install
else
	sudo make install
fi

cd ${BASEDIR}
