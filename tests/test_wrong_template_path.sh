#!/bin/bash

# wrong hello world template path will not cause segment fault

ret=`echo template path=${HOME}/.wuliao/ppp unavaliable`
res=`wuliao -t ppp`

if [ "$ret" == "$res" ]; then
  exit 0
fi
exit 1