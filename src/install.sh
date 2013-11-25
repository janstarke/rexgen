#!/bin/sh

BASEDIR=$(dirname "$SCRIPT")
. ${BASEDIR}/build.sh

cd ${BUILDDIR}

cmake ..
sudo make install

cd ${BASEDIR}
