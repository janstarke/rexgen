#!/bin/sh -e

. ./src/build.config

if test ! -d ${BUILDDIR}; then
	mkdir ${BUILDDIR}
fi

echo "entering ${BUILDDIR}"
OLD_CWD=$(pwd)
cd ${BUILDDIR}

echo "running >>> cmake ${CMAKE_OPTIONS} ${BASEDIR}/src <<<"
cmake ${CMAKE_OPTIONS} ${BASEDIR}/src && make

cd ${OLD_CWD}
