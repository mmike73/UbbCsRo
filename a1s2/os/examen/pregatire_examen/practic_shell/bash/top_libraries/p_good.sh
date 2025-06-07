#!/bin/bash

if [ $# -lt 2 ]; then
    echo "Usage: ./p.sh [number_of_libs] [file1.c] [file2.c] ..."
    exit 1
fi

N=$1
shift  # Shift to move past the first argument (number_of_libs)
args=("$@")

# Temporary file to store headers
tmpfile=$(mktemp)

# Extract headers from each file
for arg in "${args[@]}"; do
    if [ -f "$arg" ]; then
        grep -o "#include <[a-z./]\+>" "$arg" | grep -o "<[a-z./]\+>" >> "$tmpfile"
    else
        echo "Warning: File '$arg' does not exist or is not accessible."
    fi
done

# Extract unique headers
HEADERS=$(grep -o . "$tmpfile" | sort | uniq)

# Display each unique header
for header in $HEADERS; do
    echo "$header"
done

declare -A CNT

# Count occurrences of each header
while IFS= read -r header; do
    ((CNT["$header"]++))
done < "$tmpfile"

# Sort and get the top N headers
sorted=$(for lib in "${!CNT[@]}"; do
    echo "${CNT[$lib]} $lib"
done | sort -nr | head -n "$N")

echo "+++++++++ Top $N libraries ++++++++++"
echo "$sorted"

# Clean up temporary file
rm "$tmpfile"

