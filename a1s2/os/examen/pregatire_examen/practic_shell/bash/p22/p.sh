#!/bin/bash

if [ $# -ne 1 ];then
	echo Numar insuficient de argumente.
	echo utilizare: ./script.sh fisier_cuvinte
	exit 1
fi

declare -A WORDS

X=0
while IFS= read -r WRD; do
	WORDS["$X"]="$WRD"
        X=$(( X + 1 ))
done < "$1"
TOTAL=0
N=1
FN=""

while [ $N -ne 0 ];do
	echo "Introdu un numar 0 <= N < 10: "
	read N
	if [ $N -ne 0 ]; then

	echo "Introdu un nume de fisier: "
	read FN

	touch "$FN"

	CRT=0
	PROP=""
	while [ $CRT -lt $N ] && [ $TOTAL -lt $X ];do
		PROP="$PROP ${WORDS[$TOTAL]}"	
		CRT=$(( CRT + 1 ))
		TOTAL=$(( TOTAL + 1 ))
	done
	echo "$PROP" > $FN
	if [ $TOTAL -eq $X ]; then
		break
	fi
	
	LINES=$(cat "$FN" | wc -l)
	WRDS=$(cat "$FN" | wc -w)
	CHARS=$(cat "$FN" | wc -c)

	echo "Fisier: $FN \n Linii: $LINES Cuvinte: $WRDS Caractere: $CHARS"

	fi
	
done
