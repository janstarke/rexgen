#!/bin/sh -e

. ./build.config
. ${BASEDIR}/build.sh

cd ${BUILDDIR}

cmake ..

sudo make install

cd ${BASEDIR}
