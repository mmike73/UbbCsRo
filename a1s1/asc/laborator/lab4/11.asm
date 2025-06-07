bits 32

global start

extern exit

import exit msvcrt.dll

segment data use32 class=data

    a db 11111111b
    b dw 1111111111111111b
    c resb 1

segment code use32 class=code

;al: FF
start:

    ;punem bitii 2-5 ai lui a incepand de la pozitia 0
    mov al, [a]
    shl al, 2
    shr al, 4
    
    ;punem bitii 6-9 ai lui b incepand de la pozitia 4
    mov cx, [b]
    shl cx, 6
    shr cx, 12
    shl cx, 4
    
    mov ebx, 0
    mov bl, al
    add bx, cx
    
    mov eax, 0
    mov ax, bx

    
    push dword 0
    call [exit]
    
    