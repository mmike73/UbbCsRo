#!/bin/bash

SYM=$(find .)

for I in $SIM; do
	if [ -L $I ]; then
		echo "$I"
	fi
done
