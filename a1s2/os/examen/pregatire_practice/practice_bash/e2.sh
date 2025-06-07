#!/bin/bash

FILES=$(find . -type f -name "*.c")

for I in $FILES; do
	CNT_LINES=$(cat "$I" | wc -l)
	if [ $CNT_LINES -gt 500 ]; then
		FILENAME=$(echo "$I" | awk -F/ '{print $NF}')
		echo "$FILENAME" "$CNT_LINES"
	fi
done
