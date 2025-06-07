bits 32
global start

extern exit, fopen, fclose, scanf, fprintf

import exit msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll
import scanf msvcrt.dll
import fprintf msvcrt.dll

segment data use32 class=data

    nume_fisier db "numere.txt",0
    mod_acces db "w", 0
    descriptor dd 0
    n dd 0
    format db "%d", 0
    format_file db "%d - %x - %d", 0xa, 0
    
segment code use32 class=code

start:
    push mod_acces
    push nume_fisier
    call [fopen]
    add esp, 4 * 2
    mov [descriptor], eax
    rp:
        push n
        push format
        call [scanf]
        add esp, 4 * 2
    cmp dword[n], 0
    je gata
        
        mov eax, [n]
        mov edx, 0
        mov ecx, 32
        
        cnt:
            mov ebx, 1
            and ebx, eax
            add edx, ebx
            shr eax, 1
            
            cmp eax, 0
            je trm
        loop cnt
        trm:
        
        push edx
        push dword[n]
        push dword[n]
        push format_file
        push dword[descriptor]
        call [fprintf]
        add esp, 4 * 5
    jmp rp
    gata:
    
    push dword[descriptor]
    call [fclose]
    add esp, 4
    
    push dword 0
    call [exit]
    
    