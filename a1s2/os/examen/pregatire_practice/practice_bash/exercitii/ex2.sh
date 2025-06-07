#!/bin/bash

if [ $# -eq 0 ]; then
    echo "./ex2 dir1 dir2 dir3"
    exit
fi

for i in "$@"; do
    echo "$i:"
    file_content=$(grep '.' "$i")
    cnt=$(echo "$file_content" | wc -l)
    if [ "$cnt" -lt 7 ]; then
        echo "$cnt"
        echo "$file_content"
    else
	echo "$cnt"
	echo "$file_content" | head -n 3
       	echo "$file_content" | tail -n 3	
    fi
done

