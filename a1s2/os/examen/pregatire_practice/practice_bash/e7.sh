#!/bin/bash

FILE_PATH=$(find . -name "df.fake.txt" | tail -n 1)

RESULT=$(awk '{print $1, $2, $5}' "$FILE_PATH")

LINES=$(wc -l < "$FILE_PATH")

RESULT_MEM=$(awk '{print $2}' "$FILE_PATH" | sed 's/.$//' | tail -n $(($LINES-1)))
RESULT_PRC=$(awk '{print $5}' "$FILE_PATH" | sed 's/.$//' | tail -n $(($LINES-1)))

# Get the number of elements in RESULT_MEM and RESULT_PRC
num_lines=$(wc -l <<< "$RESULT_MEM")

# Iterate using the indices of RESULT_MEM and RESULT_PRC
for ((i = 1; i <= num_lines; i++)); do
    # Get the memory and percentage values at index i
    mem_value=$(sed -n "${i}p" <<< "$RESULT_MEM")
    prc_value=$(sed -n "${i}p" <<< "$RESULT_PRC")
    
    # Filter the RESULT variable based on mem_value and prc_value
    filtered_result=$(awk -v mem="$mem_value" -v prc="$prc_value" '$2 < mem || $3 < prc' <<< "$RESULT")
    
    # Print the filtered result
    echo "$filtered_result"
done



