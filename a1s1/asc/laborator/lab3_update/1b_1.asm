bits 32

global start

extern exit

import exit msvcrt.dll

segment data use32 cass=data

    a db 3
    b dw 2
    c dd 8
    d dq -6
    
segment code use 32 class=code

;(c + b + a) - (d + d)
;25 = 19h
start:
    ;c+b+a
    mov eax, [c]
    cdq
    mov ebx, eax
    mov ecx, edx
    mov al, [a]
    cbw
    cwde
    add ebx, eax
    adc ecx, 0
    
    mov eax, [b]
    cwde
    add ebx, eax
    adc ecx, 0
    
    ;(d + d)
    mov eax, [d]
    mov edx, [d + 4]
    
    add eax, dword[d]
    adc edx, dword[d+4]
    
    
    
    ;diferenta
    sub ebx, eax
    sbb ecx, edx

push dword 0
call [exit]