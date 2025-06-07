bits 32
global start
extern exit, fopen, fclose, fprintf, scanf

import exit msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll
import fprintf msvcrt.dll
import scanf msvcrt.dll

segment data use32 class=data

    n times 101 db 0
    format db "%s",0xa, 0
    
    descriptor dd 0
    nume_fisier db "numere.txt", 0
    mod_acces db "w", 0
    

segment code use32 class=code
    
make_zero:
    mov edi, n
    mov ecx, 101
    mov al, 0
    rep stosb
ret

start:
    push mod_acces
    push nume_fisier
    call [fopen]
    add esp, 4 * 2
    
    mov [descriptor], eax
    
    repeta:
        call make_zero
        push n
        push format
        call [scanf]
        add esp, 4 * 2
        
        mov esi, n
        
        parc:
            cmp byte[esi], '0'
            jb no_dig
                cmp byte[esi], '9'
                ja no_dig
                
                push n
                push format
                push dword[descriptor]
                call [fprintf]
                add esp, 4 * 3
                jmp ov
            no_dig:
            inc esi
        cmp byte[esi], 0
        je ov        
        jmp parc
        
        
        ov:
        
    cmp byte[n], '$'
    je gata
    jmp repeta
    gata:

    push dword 0
    call [exit]