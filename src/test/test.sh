#!/bin/bash -x

REXGEN_BINARY=$1
REGEX=$2
COUNT=$3
THISDIR=$(dirname $0)

if [ "x$REGEX" = "x" ]; then
	echo "Usage: $0 <regex>" >&2
	exit 1
fi

LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$(dirname $REXGEN_BINARY)

$REXGEN_BINARY -s $REGEX
CNT=$($REXGEN_BINARY -s $REGEX)
if [ "$CNT" -ne "$COUNT" ]; then
  echo "expected $COUNT result, but calculated $CNT results instead" >&2
  exit 1
fi

$RESULTS=$($REXGEN_BINARY $REGEX | perl ${THISDIR}/check_results.pl "$REGEX")

if [ "$RESULTS" -ne "$COUNT" ]; then
  echo "expected $COUNT result, but got $RESULTS results instead" >&2
  exit 1
fi
