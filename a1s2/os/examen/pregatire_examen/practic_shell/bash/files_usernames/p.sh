#!/bin/bash

if [ $# -eq 0 ]; then
       echo usage: ./p.sh [arg1] [arg2] [arg3] ...
	exit 1
fi
touch file_report.info
touch user_report.info
touch error_report.info
echo "" > file_report.info
echo "" > user_report.info
echo "" > error_report.info
F=0
U=0
E=0
for arg in "$@"; do
	FILES=`find . -type f -name "$arg"`
	if [ -z "$FILES" ];then
		FIELD=`grep "^$arg:" passwd.fake.txt`
		if [ -n "$FIELD" ]; then
			USERNAME=`echo "$FIELD" | awk -F: '{print $5}'`
			NO_PROCESSES=`echo ps.fake.txt | grep "$arg" | wc -l`
			echo "$USERNAME $NO_PROCESSES" >> "user_report.info"
			U=$(( U + 1 ))		
		else
			echo "$arg" >> "error_report.info"
			E=$(( E + 1 ))
		fi
	else
		for FILE in "$FILES"; do
			echo "$FILE" >> "file_report.info"
			sed -i -E '/ana/d' "file_report.info" >> "file_report.info"	
		done
		F=$(( F + 1 ))
	fi
done
TOTAL=$#
PF=$(( F * 100 / TOTAL ))
PU=$(( 100 * U / TOTAL ))
PE=$(( 100 * E / TOTAL ))
echo "Procent FISIERE $PF"
echo "Procent USERI   $PU"
echo "Procent ERORI   $PE"


