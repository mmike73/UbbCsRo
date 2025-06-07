#!/bin/bash

# Check if there are fewer than 4 arguments
if [ $# -lt 4 ]; then
    echo "usage: ./p.sh [word] [integer] [integer] [file1] [file2] ..."
    exit 1
fi

W="$1"
N="$2"
M="$3"
args=("${@:4}")  # Capture all arguments from the 4th onward

for arg in "${args[@]}"; do
    if [ -f "$arg" ]; then
        line=$(sed -n "${N}p" "$arg")
        OCC=$(echo "$line" | grep -o "$W" | wc -l)
        echo "$OCC"
        if [ "$OCC" -gt "$M" ]; then
            echo "$line"
        fi
    else
        echo "File '$arg' does not exist or is not a regular file."
    fi
done

