#!/bin/sh -e

. ./build.config

if test ! -d ${BUILDDIR}; then
	mkdir ${BUILDDIR}
fi

echo "entering ${BUILDDIR}"
OLD_CWD=$(pwd)
cd ${BUILDDIR}

echo "running >>> cmake ${CMAKE_OPTIONS} ${BASEDIR} <<<"
cmake ${CMAKE_OPTIONS} ${BASEDIR} && make

cd ${OLD_CWD}
