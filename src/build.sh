#!/bin/sh -e

. ./build.config

#if test -d ${BUILDDIR}; then
#	rm -rf ${BUILDDIR}
#fi

if test ! -d ${BUILDDIR}; then
	mkdir ${BUILDDIR}
fi

echo "entering ${BUILDDIR}"
cd ${BUILDDIR}

cmake -DCMAKE_BUILD_TYPE=RELEASE ..
make

echo "entering ${BASEDIR}"
cd ${BASEDIR}
