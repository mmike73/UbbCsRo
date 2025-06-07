#!/bin/bash

if [ $# -ne 3 ]; then
	echo usage: ./p.sh [directory] [number] [user]
       	exit 1	
fi

if [ ! -d $1 ]; then
	echo "Primul parametru trebuie sa fie director!"
	exit 1
fi

for file in `find "$1" -type f`; do
	echo "$file"
done

