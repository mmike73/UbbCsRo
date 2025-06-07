bits 32
global start
extern fopen, fread, printf, exit
import exit msvcrt.dll
import fread msvcrt.dll
import printf msvcrt.dll
import fopen msvcrt.dll

segment data use32 class=data

    descriptor dd 0
    nume_fisier db "numere.txt",0
    mod_acces db "r", 0
    sizee dd 1 ;dimensiunea unui element citit din fisier
    count dd 100 ;numarul maxim de elemente citite dintr-un fisier
    sir times 101 db 0
    len dd 0
    rez times 30 dd 0

segment code use32 class=code

start:
    
    