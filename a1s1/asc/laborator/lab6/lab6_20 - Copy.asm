bits 32

global start

extern exit

import exit msvcrt.dll

segment data use32 class=data

    a db "cuvant cojoc ceva ana abc"
    len equ $ - a
    b resb len
    palindrom dw 0
    
segment code use32 class=code
    start:
        mov esi, a + len - 1
        mov edi, b
     
        mov ecx, 0
        mov cx, len
        jecxz final
        std
        pal:
            movsb
            add edi, dword 2
        loop pal
        
        mov ecx, len
        jecxz final
        mov esi, a
        mov edi, b
        cld
        palin:
           cmpsb 
        loope palin
        
        jne zer
            mov [palindrom], word 06b6fh
        zer:
        final:
    
push dword 0
call [exit]