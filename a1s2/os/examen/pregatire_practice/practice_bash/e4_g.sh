#!/bin/bash

# Check if directory argument is provided
if [ $# -eq 0 ]; then
    echo "Usage: $0 directory"
    exit 1
fi

# Check if the provided argument is a directory
if [ ! -d "$1" ]; then
    echo "$1 is not a directory"
    exit 1
fi

# Find all symbolic links in the given directory recursively
find "$1" -type l | while read -r link; do
    # Check if the symbolic link points to a non-existent file or directory
    if [ ! -e "$link" ]; then
        echo "Broken symbolic link: $link"
    fi
done

