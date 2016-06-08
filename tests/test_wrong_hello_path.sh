#!/bin/bash

# wrong hello world template path will not cause segment fault

ret=`echo hello-world template path=${HOME}/.wuliao/ppp unavaliable`
res=`wuliao -w ppp`

if [ "$ret" == "$res" ]; then
  exit 0
fi
exit 1