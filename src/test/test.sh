#!/bin/bash -x

REXGEN_BINARY=$1
REGEX=$2
THISDIR=$(dirname $0)

if [ "x$REGEX" = "x" ]; then
	echo "Usage: $0 <regex>" >&2
	exit 1
fi

LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$(dirname $REXGEN_BINARY)

$REXGEN_BINARY $REGEX | perl ${THISDIR}/check_results.pl "$REGEX"
