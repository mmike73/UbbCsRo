#!/bin/bash

if [ $# -eq 0 ]; then # if
	echo Call format: ./ex7.sh file1 file2 ...
	exit 1 # if if
fi
echo "Introdu cuvantul de inlocuit: "
read CUV_DE
echo "Introdu cuvantul inlocuitor: "
read CUV_IN

for i in "$@"; do
	if [ -e "$i" ]; then  # if
		sed "s/$CUV_DE/$CUV_IN/g" "$i"
	else
		echo "File $i not found!"
	fi
done
