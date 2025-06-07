#!/bin/bash
#!/bin/bash
#!/bin/bash
#!/bin/bash
#!/bin/bash
#!/bin/bash

if [ $# -lt 1 ]; then
	echo "Call format: ./ex4 nume_director"
	exit 1
elif [ $# -eq 1 ]; then
	files=$(find "$1" -type f)
	for i in $files; do
		count=$(grep -c "[1-9][0-9]\{5\}" "$i")
		if [ $count -ne 0 ]; then
			echo "$i"
		fi
	done	
else
	echo "Invalid number of parameters!"
fi
