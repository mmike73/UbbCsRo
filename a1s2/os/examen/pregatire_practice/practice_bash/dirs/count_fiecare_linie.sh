#!/bin/bash

while IFS= read -r FILE; do
    echo "$FILE missisipi"
    echo "$FILE" | grep -o 'mere' | wc -l
done < nr_aparitii


