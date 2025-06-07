bits 32

global start

extern exit

import exit msvcrt.dll

segment data use 32 class=data

    a DB 30
    b DW 10
    c DD 700
    d DQ 20

segment code use 32 class=code

;c - ( a + d) + ( b + d)
;680 = 2a8h
start:
    mov eax, [c]
    mov edx, 0
    
    ;a + d
    mov ebx, [d]
    mov ecx, [d + 4]
    
    push ecx
    clc
    
    mov ecx, 0
    mov cl, [a]
    
    add ebx, ecx
    
    pop ecx
    adc ecx, 0
    
    ;c - (a + d)
    clc
    sub eax, ebx
    sbb edx, ecx
    
    ;b + d
    mov ebx, [d]
    mov ecx, [d + 4]
    
    push ecx
    mov ecx, 0
    mov cx, [b]
    
    clc
    add ebx, ecx
    pop ecx
    adc ecx, 0
    
    ;+(b + d) 
    clc
    add eax, ebx
    adc edx, ecx
    
    
    push dword 0
    call [exit]
    
    
    
    
    