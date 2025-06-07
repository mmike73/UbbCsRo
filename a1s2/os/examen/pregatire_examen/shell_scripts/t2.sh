#!/bin/bash

for f in ./*.txt; do
	N=`grep -o -e 'cat' $f | wc -l`
	if [ $N != 0 ]; then
		echo $f;
	fi
done
