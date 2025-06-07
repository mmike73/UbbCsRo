#!/bin/bash

ls -l / > file_stdout.tx

#grep da * 4 2> file_stderror.txt

grep da * 1>&2 > dada.txt #stdout and stderr to the same file descriptor
grep da * 2>&1 #STDERR to the file descr of stdout

ls -l $(find / -name core) &> /dev/null

#/dev/null - garbage
