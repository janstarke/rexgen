#!/bin/sh -e

. ./src/build.config
. ${BASEDIR}/build.sh

cd ${BUILDDIR}

cmake ..

sudo make install

cd ${BASEDIR}
