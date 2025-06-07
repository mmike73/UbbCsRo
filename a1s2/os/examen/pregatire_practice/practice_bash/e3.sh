#!/bin/bash

FILES=$(find . -type f -name "*.log")

for I in $FILES; do
	cat "$I" | sort > "$I".sorted
done
