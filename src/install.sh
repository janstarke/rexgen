#!/bin/sh -e

BASEDIR=$(dirname "$SCRIPT")
. ${BASEDIR}/build.sh

cd ${BUILDDIR}

cmake ..

if test $(id -u) -eq 0; then
	make install
else
	echo "you need superuser permissions to use this simplified install script"
fi

cd ${BASEDIR}
