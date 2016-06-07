#!/bin/bash

ret='This is GO and this is Python, say hello to each other guys.'

res=`./wuliao -1=GO -t=$(pwd)/tests/template.md`

if [ "$ret" == "$res" ]; then
  exit 0
fi
exit 1