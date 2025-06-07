#!/bin/bash

if [ $# -eq 0 ]; then
	echo usage: ./p.sh [directory]
	exit 1
fi
LINES=0
FILES=0
if [ -d $1 ]; then
	COMM=0

	for file in `find "$1" -type f -name "*.c"`; do
		NR_L=$(grep . "$file" | wc -l)
		LINES=$(( LINES + NR_L ))
		FILES=$(( FILES + 1 ))
		COMM=$(grep "[/]\{2,\}" "$file" | wc -l)
		echo "$file are $COMM linii comentate"	
	done
	echo "In medie $(( LINES / FILES )) linii de cod" | column -t
else
	echo "Emter a directory!!!"
fi
