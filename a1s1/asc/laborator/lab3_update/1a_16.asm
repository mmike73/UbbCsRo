bits 32

global start

extern exit

import exit msvcrt.dll

segment data use 32 class=data

    a db 40
    b dw 400
    c dd 1000
    d dq -6

segment code use 32 class=code
;c - a - (b + a) + c
;1520 = 5f0h
start:

    mov eax, [c]
    
    mov edx, 0
    mov dl, [a]
    
    mov ecx, 0
    mov cx, [b]
    add cx, dx
    
    sub eax, edx
    sub eax, ecx
    
    add eax, [c]
   
push dword 0
call [exit]
    