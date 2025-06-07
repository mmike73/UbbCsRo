bits 32
global start
extern exit, printf, cel_mai_lung_prefix
import exit msvcrt.dll
import printf msvcrt.dll

segment data use32 class=data
    
    s1 db "marian"
    l1 dd $ - s1
    s2 db "marianandrei@aof"
    l2 dd $ - s2
    s3 db "marianandrei%aof"
    l3 dd $ - s3
    rez resb 101
    len dd 0
    form db "Cel mai lung prefix este: %s.", 0
    
segment code use32 class=code


start:
    push s3
    push s2
    push s1
    push dword[l1]
    ;push dword 0
    call cel_mai_lung_prefix
    add esp, 4 * 3
    
    mov [len], eax
    mov ecx, eax
    
    mov esi, s1
    mov edi, rez
    cpy:
        mov al, [esi]
        stosb
        inc esi
    loop cpy
    
    push rez
    push form
    call [printf]
    add esp, 4 * 2
    
    push dword 0
    call [exit]
    
    
    
    