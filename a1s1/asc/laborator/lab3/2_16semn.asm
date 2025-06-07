bits 32

global start

extern exit

import exit msvcrt.dll

segment data use32 class=data

    x dq 123456h
    a dw 12h
    c dw 16h
    b db 10h
    d db 14h
    e dd 45h
    

segment code use32 class=code

;x/2+100*(a+b)-3/(c+d)+e*e
start:
    ;x / 2
    mov eax, dword[x]
    mov edx, dword[x+4]
    mov ecx, 2
    idiv ecx
    
    push eax;x / 2
    
    ;100 * (a + b)
    mov ecx, 0
    mov cx, [a]
    mov bx, 0
    mov bl, [b]
    add cx, bx
    
    mov eax, ecx
    mov cx, 100
    imul cx
    
    push eax;100 * (a + b)
    
    ;3 / ( c + d)
    
    mov ebx, 0
    mov bl, [d]
    add bx, [c]
    
    mov eax, 3
    idiv ebx
   
    push ax;3 / ( c + d)
    
    mov eax, [e]
    mov ebx, [e]
    imul ebx
    
    ;grand total
    mov ebx, 0
    pop bx
    sub eax, ebx
    sbb edx, 0
    
    pop ebx
    add eax, ebx
    adc edx, 0
    
    pop ebx
    add eax, ebx
    adc eax, 0
    
push dword 0
call[exit]