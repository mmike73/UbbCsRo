#!/bin/bash

if [ $# -eq 0 ]; then
	echo "usage: ./p.sh dir1 dir2 ..."
	exit 1
fi

DIR="$1"

FLS=`find "$DIR" -type f`

for filename in $FLS; do
	crt_name=`echo "$filename" | awk -F/ '{print $NF}'`
	#crt_name=$(basename "$filename")
	for arg in "$@"; do
		if [ "$crt_name" = "$arg" ];then
			SIZE=$(wc -c < "$filename")
			echo "$filename has size $SIZE"
		fi
	done	
done
