#!/bin/bash

if [ $# -eq 0 ]; then
	echo "Call format: ./ex5.sh elem1 elem2 ..."
	exit 1
fi

for i in "$@"; 
do
	if [ -e "$i" ]; then
		file_type=$(file -b "$i")
		if [ "$file_type" = "directory" ]; then
			echo $i `find . -type f | wc -l`
		elif [ "$file_type" = "ASCII text" ]; then
			echo $i `wc -c < "$i"` `wc -l < $i`
		fi
	else
		echo "File $i not found!"
	fi
done
