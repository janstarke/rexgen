#!/bin/bash

REGEX=$1

if [ "x$REGEX" = "x" ]; then
	echo "Usage: $0 <regex>" >&2
	exit 1
fi

LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$(dirname $0)/../build/librexgen/
REXGEN_BINARY=$(dirname $0)/../build/rexgen/rexgen

echo -n $REGEX
echo -n :
$REXGEN_BINARY $REGEX | md5sum
