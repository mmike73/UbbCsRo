#!/bin/bash

if [ -z "$1" ]; then
	echo usage $0 directory
	exit
fi

./$1".sh"

