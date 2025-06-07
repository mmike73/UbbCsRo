bits 32
global cel_mai_lung_prefix

segment code use32 public code

cel_mai_lung_prefix:
    mov esi, 0
    mov ecx, [esp + 4]
    parc:
        mov eax, [esp + 16]
        add eax, esi
        mov al, byte[eax]
        mov ebx, [esp + 8]
        add ebx, esi
        mov bl, byte[ebx]
        cmp al, bl
        jne gata
        inc esi
    loop parc
    gata:
    mov eax, esi
ret
