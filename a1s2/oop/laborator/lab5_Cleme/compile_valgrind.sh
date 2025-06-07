#!/bin/bash

gcc -Wall -g -o farmacie ui.c ui.h medicament.c medicament.h myList.c myList.h service.c service.h teste.c teste.h

valgrind -s ./farmacie

