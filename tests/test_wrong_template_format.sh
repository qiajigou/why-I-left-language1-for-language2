#!/bin/bash

ret=`echo ERR: template in $(pwd)/tests/wrong.md is invalid, maybe lost { or }?`

res=`wuliao -1 GO -t $(pwd)/tests/wrong.md`

if [ "$ret" == "$res" ]; then
  exit 0
fi
exit 1
