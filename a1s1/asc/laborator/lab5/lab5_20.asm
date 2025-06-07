bits 32

global start

extern exit

import exit msvcrt.dll

segment data use32 class=data

    A db 2, 1, 3, 3, 4, 2, 6
    la equ $ - A
    B db 4, 5, 7, 6, 2, 1
    lb equ $ - B
    R db 13
    ;R: 1, 2, 6, 7, 5, 4, 2, 4, 2, 6

segment code use32 class=code
  
start:

    mov ecx, lb
    mov esi, lb
    mov edi, 0
    
    jecxz final
    
    
    
        copiaza_b_invers:
            mov al, [B + esi - 1]
            mov [R + edi], al
            dec esi
            inc edi
        
        loop copiaza_b_invers
        
    mov ecx, la
    mov esi, 0
    
    jecxz final
    mov dl, 2
    copiaza_pare_a:
        mov al, [A + esi]
        cbw
        
        div dl
        
        cmp ah, 0
        
        jne not_par  
            mov al, [A + esi]
            mov [R + edi], al
            inc edi     
        not_par:
        
        
        inc esi
    loop copiaza_pare_a
    
    final:

push dword 0
call [exit]