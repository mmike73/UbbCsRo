bits 32
global start
extern exit, fprintf, fopen, fclose

import exit msvcrt.dll
import fprintf msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll

segment data use32 class=data

    nume_fisier db "numar.txt", 0
    mod_acces db "w", 0
    format db "%c", 0xa, 0
    n dd 1a2b3ch
    descriptor dd 0
    
segment code use32 class=code
start:
    push mod_acces
    push nume_fisier
    call [fopen]
    add esp, 4 * 2
    
    mov [descriptor], eax
    
    mov eax, [n]
    mov ecx, 16
    mov edx, 0Fh
    
    
    parc:
        push eax
        mov edx, 0fh
        and eax, edx
        
        cmp al, 9
        ja mai_mare
        add eax, '0'
        jmp atat
        mai_mare:
        add eax, 'W'
        atat:
        
        push eax
        push format
        push dword [descriptor]
        call [fprintf]
        add esp, 4 * 3
        
        pop eax
        shr eax, 4
    cmp eax, 0
    je gata
    loop parc
    gata:
    
    push dword[descriptor]
    call [fclose]
    
    push dword 0
    call [exit]
    
    