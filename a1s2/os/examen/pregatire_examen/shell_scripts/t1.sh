#!/bin/bash
ls -l
for f in $1'.'.c; do
	chmod 600 $f
done
