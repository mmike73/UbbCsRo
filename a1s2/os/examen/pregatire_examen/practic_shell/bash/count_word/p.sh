#!/bin/bash

if [ $# -lt 2 ]; then
        echo usage: ./p.sh [word] [file1] [file2] ...
        exit 1
fi

W="$1"
TOTAL=0
args=(
	${@:2}")
for arg in "${args[@]}"; do
	echo "$arg"
        if [ -f "$arg" ]; then
                OCC=$(grep -wo "$W" "$arg" | wc -l)
                TOTAL=$((TOTAL+OCC))
        fi
done

echo "$TOTAL occurences of $W"                             
