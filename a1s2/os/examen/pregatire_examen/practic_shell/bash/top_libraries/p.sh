#!/bin/bash

if [ $# -lt 2 ]; then
	echo "Usage: ./p.sh [number_of_libs] [file1.c] [file2.c]"
	exit 1
fi

N=$1
args=("${@:2}")
touch headers.txt
for arg in "${args[@]}"; do
	if [ -f "$arg" ]; then
		grep "#include <[a-z./]\+>" "$arg" >> headers.txt
	fi
done

HEADERS=$(grep -o "<[a-z./]\+>"  headers.txt | sort | uniq)

for i in $HEADERS; do
	echo $i
done

declare -A CNT

for i in `grep . headers.txt`;do
	((CNT["$i"]++))
done

sorted=$(for lib in "${!CNT[@]}"; do
	echo "${CNT[$lib]} $lib" 
done | sort -nr | head -n "((N + N))")

echo "+++++++++ Top $N libraries ++++++++++"
echo "$sorted"

rm headers.txt
