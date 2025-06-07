#!/bin/bash

if [ $# -eq 0 ]; then
	echo usage: ./p.sh [file1] [file2] ...
	exit 1
fi

for arg in $@; do
	if [ -f "$arg" ];then
		FREQ=$(grep -o '\b[1-9]*[02468]\+\b' "$arg" | wc -l)
		echo In fisierul $arg sunt $FREQ numere pare.
	fi
done
