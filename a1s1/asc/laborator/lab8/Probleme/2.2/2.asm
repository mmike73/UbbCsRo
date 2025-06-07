bits 32
global start
extern fopen,fread,printf, exit

import fopen msvcrt.dll
import fread msvcrt.dll
import printf msvcrt.dll
import exit msvcrt.dll

segment data use32 class=data
    
    nume_f db "text.txt", 0
    mod_acces db "r", 0
    descriptor resd 1
    count db 100
    sizee db 1
    text resb 100
    dimensiune dd 0
    vocale db "aeiou", 0
    format db "In text sunt %d consoane.", 0

segment code use32 class=code

start:
    ;FILE * fopen(const char* nume_fisier, const char * mod_acces)
    push mod_acces
    push nume_f
    call [fopen]
    add esp, 4 * 2
    
    mov [descriptor], eax
    
    ;int fread(void * str, int size, int count, FILE * stream)
    push dword[descriptor]
    push dword[count]
    push dword[sizee]
    push text
    call [fread]
    add esp, 4 * 4
    
    mov [dimensiune], eax
    
    mov esi, 0
    mov edi, 0
    mov ecx, dword[dimensiune]
    mov eax, 0
    jecxz final
    count_cons:
        mov al, [text + esi]
        
        push ecx
        mov ecx, 5
        mov ebx, 0
        vocals:
            cmp [vocale + ecx - 1], al
            jne nu_voc
                inc ebx
            nu_voc:
        loop vocals
        pop ecx
        cmp ebx, 0
        jne voc
            inc edi
        voc:
        inc esi
    loop count_cons
    
    push dword edi
    push format
    call [printf]
    add esp, 4 * 2

    final:
    push dword 0
    call [exit]