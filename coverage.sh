#!/bin/bash

ARGUMENT_LIST=(
  "binary"
  "profraw"
  "profdata"
)

usage() {
  echo "coverage.sh --binary <binary> --profraw <default.profraw> --profdata <default.profdata>"
}

LLVM_ROOT=/usr/local/Cellar/llvm/8.0.0/
PROFDATA=${LLVM_ROOT}/bin/llvm-profdata
COV=${LLVM_ROOT}/bin/llvm-cov

opts=$(getopt \
    --longoptions "$(printf "%s:," "${ARGUMENT_LIST[@]}")" \
    --name "$(basename "$0")" \
    --options "" \
    -- "$@"
)

eval set --$opts

while [[ $# -gt 0 ]]; do
  case "$1" in 
    --binary)
      binary=$2
      shift 2
      ;;

    --profraw)
      profraw=$2
      shift 2
      ;;

    --profdata)
      profdata=$2
      shift 2
      ;;

    *)
      #break
      shift
      ;;
  esac
done

if [ "x${binary}" == "x" ]; then usage; exit 1; fi
if [ "x${profraw}" == "x" ]; then usage; exit 1; fi
if [ "x${profdata}" == "x" ]; then usage; exit 1; fi

if [ ! -r "${binary}" ]; then
  echo "unable to read binary: ${binary}" >&2
  exit 1
fi

if [ ! -r "${profraw}" ]; then
  echo "unable to read profile data from ${profraw}" >&2
  exit 1
fi

${PROFDATA} merge -sparse ${profraw} -o ${profdata}
${COV}      report ${binary} -instr-profile=${profdata}
