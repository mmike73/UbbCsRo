#!/bin/bash

#verificarea numarului de argumente
if [ $# -eq 0 ] #$# numarul de argumente din linia de comanda
then
	echo "Numar insuficient de argumente"
	echo "Utilizare: $0 N"
	exit 1
fi

N=$1
for X in $(seq 1 $N)
do
	touch "file_$X.txt"
	sed -n ''$X',+5p' /etc/passwd >"file_$X.txt"
done
