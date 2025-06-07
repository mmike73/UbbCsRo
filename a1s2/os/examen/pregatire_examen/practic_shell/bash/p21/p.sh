#!/bin/bash

if [ $# -ne 2 ]; then
	echo usage: ./p.sh comenzi fisier
	exit 1
fi

if [ -f "$1" ]; then
	while IFS= read COMM; do
		
		C=`echo "$COMM" | awk '{print $1}'`
		E=`echo "$COMM" | awk '{print $2}'`
		V=`echo "$COMM" | awk '{print $3}'`
		if [ "$E" = "WORD" ]; then
			R=`echo "$COMM" | awk '{print $4}'`
			sed "s/${V}/${R}/g" "$2" > "propozitii"
		elif [ "$E" = "LINE" ]; then 
			if [ "$C" = "INSERT" ]; then
				R=`echo "$COMM" | awk '{print $4}'`
				sed "${V}i ${R}" "$2" > "propozitii"
			else
				sed "$a ${V}" "$2" > ""
			fi
		elif [ "$E" = "CHAR" ]; then
			sed "s/${V}/ /g" "$2" > "propozitii"
		fi

	done < "$1"
fi
