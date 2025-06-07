bits 32

global start

extern exit, fopen, fread, fclose, printf

import exit msvcrt.dll
import fopen msvcrt.dll
import fread msvcrt.dll
import fclose msvcrt.dll
import printf msvcrt.dll

segment data use32 class=data
    
    format db "In text sunt %d cifre impare", 0
    continut resb 101
    contor dw 0
    descriptor dd 0
    nume_fisier db "numere_pare.txt", 0
    mod_acces db "r", 0
    count db 100
    size_of_element db 1
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
    push dword [descriptor]
    push dword [count]
    push dword [size_of_element]
    
    push continut
    call [fread]
    add esp, 4 * 4
    
    mov [lth], eax
    ;parcurgere si numarare
    mov ecx, [lth]
    jecxz final
    mov esi, 0
    mov bl, 2
    parcurge:
   
        mov al, [continut + ecx - 1]
        sub al, byte '0'
        cbw
        
        cmp al, 9
        ja impar
        cmp al, 0
        jb impar
        div bl
        
        cmp ah, byte 1        
        je impar     
            inc esi
        impar:
    
    loop parcurge
    
    final:
    
    push esi
    push dword format
    call [printf]
    
    push dword[descriptor]
    call [fclose]
    add esp, 4
    
    
    push dword 0
    ;call [exit]