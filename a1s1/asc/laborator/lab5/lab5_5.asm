bits 32

global start

extern exit

import exit msvcrt.dll

segment data use32 class=data

    s db 'a','A','b','B2','%','x'
    len equ $ - s
    d times len db 0
    ;d: 'a', 'b', 'x'
    
segment code use32 class=code

start:
    
    mov ecx, len
    mov esi, 0
    mov edi, 0
    jecxz final
    
    repeta:
        mov al, [s + esi]
        inc esi
        cld
        cmp al, 'a'
        jnge mare_a
            cmp al, 'z'
            jnle mic_z
                
                mov [d + edi], al
                inc edi
                
            mic_z:
        mare_a:
        
    loop repeta

    final:
push dword 0
call [exit]