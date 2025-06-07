bits 32

global start

extern exit

import exit msvcrt.dll

segment data use32 class=data

    s1 db  7, 33, 55, 19, 46
            
    len1 equ $-s1
    
    s2 db 33, 21,  7, 13, 27, 19, 55, 1, 46   
    
    len2 equ $-s2   
    
    d times len2 db 0
    
    
    s3 db 1,2,3,4,5
        
    ;se cere in d pozitiile la care aar elementele din s2 in s1 sau 0 in ca contrar
    
segment code use32 class=code

start:

    mov ecx, len1 ;se va cicla de len ori
    jecxz final
    
    mov esi, 0  ;index in s1
    
    outer_loop:
    ;ia fiecare element din primul vector si comapara elementele cu cele din al doilea
        mov al, [s1 + esi]
        mov edi, s2 ;index in s2 si d
        push ecx
        mov ecx, len2
        repeta:
            scasb
            jne egal
                mov edx, edi
                sub edx, s2
                
                dec edx
                push eax
                mov eax, esi
                inc al
                mov [edx + d], al
                pop eax
                inc edi
            egal:
            
            loop repeta
        pop ecx
        inc esi
    loop outer_loop
    
    final:

push dword 0
call [exit]