bits 32
global convert
segment code use32 public code

convert:
    mov esi, [esp + 4]
    mov ecx, 32
    mov ebx, 0
    cv:
        lodsb
        cmp al, 0
        jz over
        sub al, '0'
                
        shl ebx, 1
        add bl, al
    loop cv
    over:
    mov eax, ebx
ret