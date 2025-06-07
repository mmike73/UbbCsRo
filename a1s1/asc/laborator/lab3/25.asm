bits 32

global start

extern exit

import exit msvcrt.dll

segment data use32 class=data

    a dw 10h
    b db 12h
    c dd 7h
    x dq 1000000000000dh
    
segment code use32 class=code

start:
    ;(a * a + b + x) / (b * b) + c * c
    ;(a * a + b + x)
    mov eax, 0
    mov ax, [a]
    mov bx, [a]
    imul bx
    mov ebx, 0
    mov bl, [b]
    add eax, ebx
    mov edx, 0
    adc edx, 0
    
    add eax, dword[x]
    adc edx, dword[x + 4]
    
    
    push eax
    push edx
    
    mov eax, [c]
    imul dword[c]
    
    mov eax, ebx
    mov edx, ecx
    
    pop edx
    pop eax
    
    push ebx
    push ecx
    
    mov ebx, 0
    add ebx, [b]
    add ebx, [b]
    
    idiv ebx
    
    pop ebx
    add eax, ebx
    adc edx, 0
    
push dword 0
call [exit]

