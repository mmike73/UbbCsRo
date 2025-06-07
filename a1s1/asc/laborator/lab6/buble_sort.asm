bits 32

global start

extern exit

import exit msvcrt.dll

segment data use32 class=data

    sir dd 4,7,1,5,2,9
    len equ ($ - sir) / 4
    ok db 0
    ;
    
segment code use32 class=code

start:
    
    mov ecx, 1
    
    mov esi, 0
    
    cat_timp_nu_sortat:
        mov [ok], byte 1
        
        push ecx
        mov ecx, len
        dec ecx
        parcurge_sir:
            mov edx, dword[sir + esi]
            cmp edx, dword[sir + esi + 4]
            jbe swap
                mov [ok], byte 0
                mov eax, dword[sir + esi + 4]
                mov dword[sir + esi], eax
                mov [sir + esi + 4], edx
            swap:
            
        loop parcurge_sir
        
        cmp [ok], byte 0
        pop ecx
        jnz sortat
            dec ecx
        sortat:
        inc ecx
        
    loop cat_timp_nu_sortat
    



push dword 0
call [exit]

