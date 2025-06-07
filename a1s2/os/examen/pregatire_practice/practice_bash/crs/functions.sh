#!/bin/bash

function quit {
	exit
}

function hehe {
	echo Inceput;
	i=1;
	j=$#;
	while [ $i -le $j ]
	do
		echo "$i $1";
		i=$((i + 1));
		shift 1;
	done
	exit	
	echo Nu trebuie afisat
}



hehe
hehe
