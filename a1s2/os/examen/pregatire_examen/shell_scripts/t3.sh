#!/bin/bash
N=0
T=0
for f in ./*.txt; do
	N=$((N + 1));
	TMP=$(grep . "$f" | wc -l)	
	T=$((T + TMP)); 
done

echo $N fisiere cu media de $((T/N)) cuvinte
