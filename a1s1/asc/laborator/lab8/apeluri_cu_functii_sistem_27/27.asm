bits 32
global start

extern printf, exit, scanf

import printf msvcrt.dll
import scanf msvcrt.dll
import exit msvcrt.dll

segment data use32 class=data

    s db "afhalkfhncalkhfalkfhnalajcjflajfkkwhr",0
    len equ $ - s
    format db "Sirul de caractere contine litera %c de %d ori.", 0
    form_c db "Introdu o litera: ", 0
    form_rc db "%c", 0
    c db 0
    
segment code use32 class=code

start:
    push form_c
    call [printf]
    add esp, 4
    
    push c
    push form_rc
    call [scanf]
    add esp, 4 * 2
    
    mov ecx, dword len
    mov ebx, 0
    mov bl, [c]
    mov edx, 0
    parc:
        cmp byte[s + ecx - 1], bl
        jne cont
            inc edx
        cont:
    loop parc
    
    push edx
    push ebx
    push format
    call [printf]
    add esp, 4 * 3
    
    push dword 0
    call [exit]