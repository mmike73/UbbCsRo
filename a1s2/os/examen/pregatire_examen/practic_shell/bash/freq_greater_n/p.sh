#!/bin/bash

if [ $# -lt 2 ]; then
	echo usage: ./p.sh [number] [file1] [file2] ...
	exit 1
fi

N=$1
#to shift all the arguments with one position
shift

declare -A map

for file in "$@"; do
	touch tmpfile
	ALL=(`grep "[a-z]\+" $file`)
	for crt in "${ALL[@]}"; do
		((map["$crt"]++))	
	done
	for key in "${!map[@]}"; do
		if [ ${map[$key]} -ge $N ]; then
			echo "$key"		
		fi
	done
	rm tmpfile
	A=()
done
