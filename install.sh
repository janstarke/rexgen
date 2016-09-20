#!/bin/sh -e

. ./src/build.config
. ${BASEDIR}/build.sh

( cd ${BUILDDIR}; sudo make install)

