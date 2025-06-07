bits 32
global start
extern exit, fopen, fclose, fread, printf

import exit msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll
import fread msvcrt.dll
import printf msvcrt.dll

segment data use32 class=data

    format db "In text sunt %d cuvinte.|", 0
    nume_fisier db "text.txt", 0
    mod_acces db "r", 0
    text resb 100
    sizee dd 1
    count dd 100
    descriptor resd 1
    lth dd 0

segment code use32 class=code

start:
    
    ;FILE * fopen(const char* nume_fisier, const char * mod_acces)
    push dword mod_acces
    push dword nume_fisier
    call [fopen]
    mov [descriptor], eax
    add esp, 4 * 2
    
    ;int fread(void * str, int size, int count, FILE * stream)
    push dword[descriptor]
    push dword[count]
    push dword[sizee]
    push text
    call [fread]
    add esp, 4 * 4
    mov [lth], eax
    
    mov ebx, 0
    mov esi, 0
    mov edi, 0
    mov edx, 0
    
    mov ecx, [lth]
    jecxz final
    outer:
        cmp [text + esi], byte'a'
        jb nu_e_litera
        cmp [text + esi], byte'z'
        ja nu_e_litera
    
        inc edi
        jmp fin
        
        nu_e_litera:
        
        cmp edi, 0
        je nu_e_cuv
            inc ebx
        nu_e_cuv:        
        mov edi, 0 
        
        fin:
        inc esi
        
    loop outer
    
    cmp edi, 0
    je n_c
        inc ebx
    n_c:
    
    push dword ebx
    push format
    call [printf]
    add esp, 4 * 2
    
    
    final:
    
    push dword[descriptor]
    call [fclose]
    add esp, 4 * 1
    
    push dword 0
    call [exit]
    
    
    
    
    