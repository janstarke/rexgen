#!/bin/sh -e

. ./src/build.config

if test -d ${BUILDDIR}; then
	rm -rf ${BUILDDIR}
fi
