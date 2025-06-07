bits 32
global start
extern scanf, printf, exit, lege

import scanf msvcrt.dll
import printf msvcrt.dll
import exit msvcrt.dll

segment data use32 class=data

    format db "Introdu numerele: (a + b - c)",0xa,0
    format_n db "%d %d %d",0
    format_p db "Rezultatul este: %d",0
    a dd 0
    b dd 0
    c dd 0

segment code use32 class=code

start:
    push format
    call [printf]
    add esp, 4

    push c
    push b
    push a
    push format_n
    call [scanf]
    add esp, 4 * 4
    
    push dword [c]
    push dword [b]
    push dword [a]
    call lege
    add esp, 4 * 3
    
    push eax
    push format_p
    call [printf]
    add esp, 4 * 2
    
    push dword 0
    call [exit]
    
