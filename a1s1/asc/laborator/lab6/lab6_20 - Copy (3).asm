bits 32

global start

extern exit,printf , scanf

import exit msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt.dll

segment data use32 class=data

    a db "ana cojoc ccc cc asd amma ", 0

    len equ $ - a
    b resb len
    sta dd b
    l dd 0
    c_l dd 0
    
    format dd "Cuvintele palindrom sunt: %s", 0
    shit db "shit", 0
    
segment code use32 class=code
    start:
        
    ;Se da un sir de octeti reprezentand un text (succesiune de cuvinte separate de spatii). Sa se identifice cuvintele de tip palindrom (ale caror oglindiri sunt similare cu cele de plecare): "cojoc","capac" etc.

    
    mov esi, a
    mov edi, a
    mov ecx, len
    jecxz final
    add ecx, 1
    
    parc:
    cmp [edi], byte ' '
    jne litera
    dec edi
    call v_pal
    add edi, 2
    mov esi, edi
    dec edi
    litera:
    inc edi
    loop parc
    
    
    push b
    push format
    call [printf]
    
    add esp, 4 * 2
    
    
    jmp final
    
    v_pal: 
    push edi
    push ecx
    push esi
    
    mov ecx, edi
    sub ecx, esi
    add ecx, 1
    mov [l], ecx
    ;cmp ecx, 1
    ;je pal 
    
    shr ecx, 1
    
    pal:
    cmpsb
    jne not_pal
    sub edi, 2
    loop pal
    mov edi, [sta]
    pop esi
    push esi
    
    mov ecx, [l]
    
    coppy:
    cld
    mov al, [esi]
    stosb 
    inc esi
    loop coppy
    mov [edi], byte' '
    inc edi
    
    
    mov [sta], edi
    
    not_pal:
    
    
    pop esi
    pop ecx
    pop edi
    ret
    final:
push dword 0
call [exit]