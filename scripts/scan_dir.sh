#!/bin/bash

sizes=`find $1 \( -iname \*.jpg -o -name \*.jpeg  \) -exec jpeg-zero-clean {} \; | grep size | awk '{print $4}'| awk '{s+=$1} END {print s}'`
echo Additional zero bytes in all files add up to $sizes

