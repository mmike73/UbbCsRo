bits 32
global start
extern printf, scanf, exit

import exit msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt.dll

segment data use32 class=data
    
    a dw 0
    m db 0
    n db 0
    format_r db "Introdu un numar: ", 0
    format_ri db "Introdu indicii bitilor izolati: ", 0
    format_ra db "%d", 0
    format_rmn db "%d %d", 0
    format_b db "%d", 0

    
segment code use32 class=code
start:
    push format_r
    call [printf]
    add esp, 4 * 1
    
    push a
    push format_ra
    call [scanf]
    add esp, 4 * 2
    
    push format_ri
    call [printf]
    add esp, 4 * 1
    
    push n
    push m
    push format_rmn
    call [scanf]
    add esp, 4 * 3
        
    mov eax, 0
    mov ecx, 16
    mov ebx, 0
    
    set:
        cmp bl, [m]
        jb sari
        cmp bl, [n] 
        ja sari
        add eax, 1
        sari: 
        ror eax, 1
        inc ebx
    loop set  
    ror eax, 16
    
    mov bx, [a]
    and ax, bx
    
    push eax
    push format_b
    call [printf]
    add esp, 4 * 2
    
    push dword 0
    call [exit]