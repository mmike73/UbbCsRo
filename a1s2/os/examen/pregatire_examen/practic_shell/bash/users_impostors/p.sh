#!/bin/bash

if [ $# -lt 2 ];then
	echo usage: ./p.sh [file1] [file2] [username1] [username2] ...
	exit 1
fi

if [ -f $1 ] && [ -f $2 ];then
	args=("${@:3}")
	for arg in "${args[@]}"; do
		REZ=$(grep "^$arg:" passwd.fake.txt)
		if [ -n "$REZ" ];then
			NUME=$(echo "$REZ" | awk -F: '{print $5}')
			echo "$NUME"
			PATH=$(echo "$REZ" | awk -F: '{print $6}')
			SIZE=$(du -sh "." | awk '{print $1}')
			echo "$SIZE"
		else
			echo "$2" >> "$arg" 
		fi
	done
else
	echo "Shiiiiat, you need 2 directories!!!"
fi
