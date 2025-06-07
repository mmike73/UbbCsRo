#!/bin/bash

if [ $# -eq 0 ]; then
	echo usage: ./p.sh arg1 arg2 ...
	exit 1
fi

for arg in $@; do
	is_user=`grep $arg "who.fake.txt"`
	echo $is_user
	if [ "$is_user" ]; then
		username=$(cat passwd.fake.txt | grep $arg | awk -F: '{print $5}')
		$log=`who | grep $arg | wc -l`
		
		#if logged
		if [ $log -ne 0 ]; then
			nop=`cat ps.fake.txt | grep $arg | wc -l`
			echo "Nr procese: $nop"
		else
			last_login=`cat last.fake.txt | grep $arg | tail -1`
			start_s=`echo $last_login | awk '{print $7}'`
			duration=`echo $last_login | awk '{print $NF}'`
			echo "$username was last logged at $start_s for $duration hours"
		fi	
	fi

	is_file=`find -type f -name $arg 2> /dev/null`
	if [ "$is_file" ]; then
		echo file
	fi

	is_directory=`find -type d -name $arg 2> /dev/null`
	if [ "$is_directory" ];then
		echo dir
	fi
done
