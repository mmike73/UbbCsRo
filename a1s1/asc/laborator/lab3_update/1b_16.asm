bits 32

global start

extern exit

import exit msvcrt.dll

segment data use=32 class=data

    a db 40
    b dw 0
    c dd 100
    d dq 80
;20 = 14h
segment code use=32 class=code
start:
    ;(d - a) - (a - c) - d
    ;d - a
    mov ebx, [d]
    mov ecx, [d + 4]
    mov al, [a]
    cbw
    cwde
    cdq
    
    sub ebx, eax
    sbb ecx, edx
    push ebx
    push ecx
    
    
    ;a - c
    mov al, [a]
    cbw
    cwde
    cdq
    mov ebx, eax
    mov ecx, ebx
    mov eax, [c]
    cdq
    sub ebx, eax
    sbb ecx, edx
    
    ;(d-a)-(a-c)   
    pop edx
    pop eax
    sub eax, ebx
    sbb edx, ecx
    
    
    ;totul - d
    mov ebx, [d]
    mov ecx, [d + 4]
    
    sub eax, ebx
    sbb edx, ecx
    
    push dword 0
    call [exit]
    