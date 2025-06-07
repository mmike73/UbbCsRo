#!/bin/bash

USER_LIST=$(grep . dirs/who.fake.txt | awk '{print $1}' )

for I in $USER_LIST; do
	PSC=$(grep "$I" dirs/ps.fake.txt | uniq | wc -l)
	echo "$I" "$PSC"
done
