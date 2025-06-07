bits 32
global start
extern exit, fopen,fclose, fscanf

import exit msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll
import fscanf msvcrt.dll

segment data use32 class=data

    n times 10 dw 0
    nume_fisier db "numere.txt", 0
    mod_acces db "r", 0
    format db "%d", 0
    
    descriptor dd 0
    

segment code use32 class=code

start:
    push mod_acces
    push nume_fisier
    call [fopen]
    add esp, 4 * 2
    
    mov [descriptor], eax
    
    Bucla:
        push n
        push format
        push dword[descriptor]
        call [fscanf]
        add esp, 4 * 3
        cmp word[n], 0
        je Final
    jmp Bucla    
    Final:
    

    