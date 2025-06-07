#!/bin/bash

if [ $# -eq 0 ]; then
	echo "Numar insufucient de argumente"
	exit 1
fi

N=1
echo "Introdu un numar: "
read N

while [ $N -ne 0 ]; do
	for file in $@; do
		NRS=$(grep -o "\b[1-9]*[0-9]\+\b" "$file")
		TOTAL=0
		while IFS= read -r num; do
            		TOTAL=$(( TOTAL + num ))
        	done < <(grep -o '\b[1-9][0-9]*\b' "$file")
		if [ $TOTAL -lt $N ]; then
			echo "$(( N - TOTAL ))" >> "$file"
			echo written $(( N - TOTAL ))
		fi
	done
	echo "Introdu un numar: "
        read N
done
