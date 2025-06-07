bits 32
global start
extern exit, scanf, fopen, fclose, fprintf

import exit msvcrt.dll
import scanf msvcrt.dll
import fprintf msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll

segment data use32 class=data
    nv dd 0
    formatnv db "%d", 0
    
    nrvoc dd 0
    vocale db "aeiou", 0
    lv dd $ - vocale
    
    n times 101 db 0
    format db "%s", 0
    formato db "%s", 0xa, 0
    
    nume_fisier db "rezultat.txt", 0
    mod_acces db "w", 0
    
    descriptor dd 0
    
segment code use32 class=code

start:
    push mod_acces
    push nume_fisier
    call [fopen]
    mov [descriptor], eax
    
    push nv
    push formatnv
    call [scanf]
    add esp, 4 * 2
    
    lp:
        push n
        push format
        call [scanf]
        add esp, 4 * 2
        
        mov esi, n
        mov [nrvoc], dword 0
        
        parc:
            cmp byte[esi], 0
            je urm
            mov edi, vocale
            comp:
            
                cmp byte[edi], 0
                je over
                mov bl, byte[esi]
                cmp bl, byte[edi]
                jne no_good
                    inc dword[nrvoc]
                    mov ebx, [nrvoc]
                    cmp ebx, [nv]
                    jne inca_nu
                    push n
                    push formato
                    push dword[descriptor]
                    call [fprintf]
                    add esp, 4 * 3
                    jmp urm
                    inca_nu:
                no_good:
                
            
            inc edi
            jmp comp
            over:
        
        
        inc esi
        jmp parc
        
        urm:
    cmp byte[n], '#'
    je gata
    jmp lp
    gata:
    
    push dword[descriptor]
    call [fclose]
    add esp, 4 * 1
    
    push dword 0
    call [exit]