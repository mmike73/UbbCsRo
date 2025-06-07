#!/bin/bash

filenames=$(file * | grep "text$" | awk -F: '{print $1}')
cnt_lines=0
cnt_files=0
for i in $filenames; do 
	(( cnt_lines=cnt_lines+$(grep '.' "$i" | wc -l) ))
	(( cnt_files=cnt_files+1 ))
#	echo $cnt_lines $cnt_files
done
echo $(( cnt_lines/cnt_files ))

printf "Mai exact: %f\n" $((cnt_lines/cnt_files))

 

