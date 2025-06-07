#!/bin/bash

ARR=(`grep . words`)
for i in "${ARR[@]}"; do
	echo "$i"
done
