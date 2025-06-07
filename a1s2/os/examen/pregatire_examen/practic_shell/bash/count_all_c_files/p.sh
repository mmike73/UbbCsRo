#!/bin/bash

if [ $# -eq 0 ]; then
	echo "Introdu nume de directoare!"
	exit 1
fi
N=0
for arg in $@; do
	FILES=$(find $arg -type f -name "*.c" | wc -l)
	N=$((N+$FILES))	
done
echo Numarul de fisiere este $N
