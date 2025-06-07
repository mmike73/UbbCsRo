#!/bin/bash

if [ $# -eq 0 ]; then
    echo "Call format: $0 file1 file2 ..."
    exit 1
fi
echo  > tmp9
while [ $# -gt 0 ]; do
    if [ -f "$1" ]; then
        # Get the sorted list of non-empty lines along with their line numbers
        LINES=$(grep . "$1" | cat -n | sort -k2)
        NL=$(echo "$LINES" | wc -l)

        # Initialize variables for tracking current and next lines
        I=1
        J=$((I + 1))
	
	MAX=0
	

        # Loop through each line
        while [ "$I" -le "$NL" ]; do
            # Extract the current line and its count
            LINE1=$(echo "$LINES" | awk -v i="$I" '$1 == i {print substr($0, index($0,$2))}')
            CNT=1
            
            # Check for identical subsequent lines
            while [ "$J" -le "$NL" ]; do
                LINE2=$(echo "$LINES" | awk -v j="$J" '$1 == j {print substr($0, index($0,$2))}')
                if [ "$LINE1" = "$LINE2" ]; then
                    ((CNT++))
                else
                    break
                fi
                ((J++))
            done

            # Output the line and its count
	    if [ "$CNT" -gt "$MAX" ]; then
		    MAX=$CNT
		    MAXLINE=$LINE1
	    fi

            # Move to the next line
            I="$J"
            ((J++))
        done
    fi
    echo "$MAXLINE" "$MAX" >> tmp9 
    shift 1
done

#sed -i '/^$/d' tmp9 > tmp9

grep . tmp9 | sort -r -k 2
