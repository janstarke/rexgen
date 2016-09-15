#!/bin/sh -e

. ./build.config

if test -d ${BUILDDIR}; then
	rm -rf ${BUILDDIR}
fi
