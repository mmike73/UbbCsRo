#!/bin/bash

if [ $# -lt 2 ]; then
	echo usage: ./p.sh [file] [string1] [string2] ...
	exit 1
fi

while IFS= read dirname; do
	echo "dirname"
done < directories.txt
