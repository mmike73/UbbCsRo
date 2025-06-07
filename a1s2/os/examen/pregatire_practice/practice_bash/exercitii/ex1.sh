#!/bin/bash
#!/bin/bash
#!/bin/bash

if [ $# -eq 0 ];then
	echo Formatul de rulare: ./ex1 N
	exit
fi
cd de1
format="file_"
for i in `seq 1 $1`;
do
	
	touch "$format$i.txt"
	head -n `expr $i + 5` ../../dirs/passwd.fake.txt | tail -n 5 > "$format$i.txt"
done


