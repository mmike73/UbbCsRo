#!/bin/bash

if [ $# -eq 0 ]; then
        echo Call format: ./ex6.sh file1 file2 ...
        exit 1
fi

read CUVANT
for i in "$@"; do
        CNT_CUV=`grep "\b$CUVANT\b" "$i" | wc -l`
        if [ $CNT_CUV -ne 0 ]; then
                echo $i $CNT_CUV
        fi
done
