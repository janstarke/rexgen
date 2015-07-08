#!/bin/bash -x

REXGEN_BINARY=$1
REGEX=$2
COUNT=$3
THISDIR=$(dirname $0)

if [ "x$REGEX" = "x" ]; then
	echo "Usage: $0 <regex>"
	exit 1
fi

LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$(dirname $REXGEN_BINARY)

RESULTS=$($REXGEN_BINARY $REGEX | perl ${THISDIR}/check_results.pl "$REGEX")

if [ "$?" = "-1" ]; then 
  echo $RESULTS
  exit 1
fi

if [ "x$RESULTS" != "x$COUNT" ]; then
  echo "expected $COUNT results, but got $RESULTS results instead"
  exit 1
fi

exit 0
