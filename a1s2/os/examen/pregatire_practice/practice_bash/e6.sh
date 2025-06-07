#!/bin/bash

FILELIST=$(find . -type f)

for i in $FILELIST; do
	PERMISIUNI=$(ls -l "$i" | awk '{print $1}')
 	echo "Before: " "$i $PERMISIUNI" | column -t

	chmod o+rwx "$i"

	PERMISIUNI=$(ls -l "$i" | awk '{print $1}')
 	
	echo "After: " "$i $PERMISIUNI" | column -t
done
