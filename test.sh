#!/bin/bash

TESTS=`find tests/* -type f -perm -111`
EXIT_CODE=0

echo -e "\nRunning wuliao(1) tests\n"

for t in $TESTS; do
  ./$t
  if [ $? -ne 0 ]; then
    echo >&2 "  (✖) $t"
    EXIT_CODE=1
  else
    echo "  (✓) $t"
  fi
done
echo

exit $EXIT_CODE