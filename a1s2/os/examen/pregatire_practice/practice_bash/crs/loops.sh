#!/bin/bash

echo Iterates through elements:
for i in $( ls );
do
	echo item: $i
done

echo
echo Range for - C-like

for i in `seq 1 40`;
do
	echo $i th iteration		
done

COUNTER=0
while [ $COUNTER -lt 100 ];
do
	echo The counter is $COUNTER
	let COUNTER=COUNTER+1
	(( COUNTER=COUNTER+1 ))
done
echo
echo "The counter is still $COUNTER"

until [ $COUNTER -lt 0 ];
do
	echo "$COUNTER `expr 100 - $COUNTER`"
	let COUNTER-=1
done
