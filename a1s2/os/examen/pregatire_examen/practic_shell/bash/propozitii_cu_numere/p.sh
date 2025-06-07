#!/bin/bash

if [ $# -ne 1 ]; then
	echo "usage: ./p.sh [file]"
	exit 1
fi

if [ -f $1 ]; then
	touch output.txt
	N=0
	echo "Introdu un numar: "
	read N
	while [ $N -ne 0 ]; do
		CRT=""	
		IND=0
		while IFS= read -r word; do
			CRT="$CRT $word"
			IND=$(( IND + 1 ))
			if [ $IND -eq $N ]; then
				echo "$CRT" >> "output.txt"
				break
			fi
		done < "$1"

		echo "Introdu un numar: "
        	read N
	done
else
	echo "Argumentul trebuie sa fie fisier text!"
fi
