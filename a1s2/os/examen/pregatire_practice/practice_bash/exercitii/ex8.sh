#!/bin/bash

if [ $# -eq 0 ]; then
    echo "Call format: filename,word,number filename,word,number ..."
    exit 1
fi

while [ $# -gt 0 ]; do
    filename=$(echo "$1" | awk -F, '{print $1}')
    word=$(echo "$1" | awk -F, '{print $2}')
    number=$(echo "$1" | awk -F, '{print $3}')
    
    while IFS= read -r line; do
        occ=$(echo "$line" | grep -o "$word" | wc -l)
        if [ "$occ" -eq "$number" ]; then
            echo "$line"
        fi
    done < "$filename"
    
    shift 1
done

