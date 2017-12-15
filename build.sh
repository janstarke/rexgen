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

if test "x${TEST_ENABLED}" = "x1" -a $? -eq "0"; then
  lcov --gcov-tool /usr/local/bin/gcov-7 -d . -b . -z
  make test
  if test "${COVERAGE_ENABLED}" -eq "1" -a $? -eq "0"; then
    lcov --gcov-tool /usr/local/bin/gcov-7 -d . -b . -c -o librexgen.info
    lcov --gcov-tool /usr/local/bin/gcov-7 -d . -b . -r librexgen.info '*.l' -o librexgen.info
    lcov --gcov-tool /usr/local/bin/gcov-7 -d . -b . -r librexgen.info '*.y' -o librexgen.info
    genhtml -o test_coverage librexgen.info
  fi
fi


cd ${OLD_CWD}
