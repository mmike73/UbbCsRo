#!/bin/bash

if [ $# -ne 1 ];then
	echo Numar insuficient de argumente.
	echo utilizare: ./script.sh fisier_cuvinte
	exit 1
fi

N=1
FN=""
while [ $N -ne 0 ];do
	echo "Introdu un numar 0 <= N < 10: "
	read N
	if [ $N -ne 0 ]; then

	echo "Introdu un nume de fisier: "
	read FN

	touch "$FN"
	X=1
	while IFS= read -r WRD && [ $X -lt $N ]; do
		echo "$WRD"
		X=$(( X + 1 ))
	done < "$1"

	fi
	echo citit "$N" cu nume "$FN"
done
