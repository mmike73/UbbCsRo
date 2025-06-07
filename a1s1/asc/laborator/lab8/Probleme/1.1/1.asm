bits 32

global start

extern exit, scanf, printf
import printf msvcrt.dll
import exit msvcrt.dll
import scanf msvcrt.dll

segment data use32 class=data
    a dw 0 
    b dw 0
    rezultat dd 0
    format db "Introdu doua numere:", 0
    format_r db "%d %d", 0
    
segment code use32 class=code
    start:
    push format
    call [printf]
    add esp, 4
    
    push b
    push a
    push format_r
    call [scanf]
    add esp, 4 * 3
    
    mov ax, [a]
    mov bx, [b]
    imul bx
    
    mov [rezultat], eax
    
    push dword 0
    call[exit]
    
    