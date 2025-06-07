bits 32
global start 

extern scanf, printf, exit
import scanf msvcrt.dll
import printf msvcrt.dll
import exit msvcrt.dll

segment data use32 class=data

    n dd 0
    format db "Introdu un numar: %d", 0
    format_o db "Numarul introdus este: %d", 0
    
segment code use32 class=code

    start:
    
    push dword n
    push format
    call [scanf]
    
    add esp, 4 * 2
    
    push dword n
    push format_o
    call [printf]
    
    add esp, 4 * 2
    
    push dword 0
    call [exit]
    
    
    