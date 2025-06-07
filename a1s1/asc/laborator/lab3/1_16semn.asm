bits 32

global start

extern exit

import exit msvcrt.dll

segment data use32 class=data

    a db ffh
    b dd 11h
    c dq 100h

segment code use32 class=code
    
    mov eax, 0
    
    mov al, [a]
    mul byte[a]
    
    sub eax, [b]
    add eax, 7
    
    mov dx, 2
    add dx, [a]
    
    div dx
    
    add eax, dword[c]
    mov edx, 0
    adc eax, dword[c+4]

push dword 0
call [exit]