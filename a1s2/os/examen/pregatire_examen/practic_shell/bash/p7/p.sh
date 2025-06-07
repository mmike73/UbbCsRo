#!/bin/bash
 
if [ $# -lt 2 ]; then
	echo usage: ./p.sh [number] [file1] [file2] ...
	exit 1
fi
N=$1
W=$2
shift
shift
for file in $@; do
	grep "$W" "$file" | sed -n "${N}p"
done
