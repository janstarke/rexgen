#!/bin/sh -e

. ./src/build.config

if test ! -d ${BUILDDIR}; then
	mkdir ${BUILDDIR}
fi

echo "entering ${BUILDDIR}"
OLD_CWD=$(pwd)
cd ${BUILDDIR}

if [ `uname`=='Darwin' ]; then
  export CMAKE_PREFIX_PATH="/usr/local/opt/bison:/usr/local/opt/flex"
fi
echo "running >>> cmake ${CMAKE_OPTIONS} ${BASEDIR}/src <<<"
cmake ${CMAKE_OPTIONS} ${BASEDIR}/src && make -j `getconf NPROCESSORS_ONLN`

if test "x${TEST_ENABLED}" = "x1" -a $? -eq "0"; then
#  lcov --gcov-tool /usr/local/bin/gcov-7 -d . -b . -z
  make test
#  GCOV=$(which gcov-7)
#  if test "${COVERAGE_ENABLED}" -eq "1" -a $? -eq "0"; then
#    lcov --gcov-tool ${GCOV} -d . -b . -c -o librexgen.info
#    lcov --gcov-tool ${GCOV} -d . -b . -r librexgen.info '*.l' -o librexgen.info
#    lcov --gcov-tool ${GCOV} -d . -b . -r librexgen.info '*.y' -o librexgen.info
#    genhtml -o test_coverage librexgen.info
#  fi
fi


cd ${OLD_CWD}
