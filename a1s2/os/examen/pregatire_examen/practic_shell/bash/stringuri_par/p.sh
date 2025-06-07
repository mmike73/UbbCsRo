#!/bin/bash

if [ $# -eq 0 ];then 
	echo usage: ./p.sh [file1] [file2] ...
	exit 1
fi
STR=""
echo "Introdu un cuvant: "
read STR
while [ "$STR" != "stop" ]; do
	CNT=0
	for file in $@; do
		if [ -f "$file" ]; then
			CNT=$(grep "$STR" "$file" | wc -l)
			if [ $(( $CNT % 2 == 1 )) -eq 1 ]; then
				echo "$STR" >> $file
				echo "written $STR"
			fi
			echo "$file"
			echo "$CNT aparitii"
		fi	
	done
	echo "Introdu un cuvant: "
	read STR
done	
