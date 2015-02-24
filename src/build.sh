#!/bin/sh -e

. ./build.config

if test ! -d ${BUILDDIR}; then
	mkdir ${BUILDDIR}
fi

echo "entering ${BUILDDIR}"
pushd ${BUILDDIR}

echo "running >>> cmake ${CMAKE_OPTIONS} ${BASEDIR} <<<"
cmake ${CMAKE_OPTIONS} ${BASEDIR}
make

popd
