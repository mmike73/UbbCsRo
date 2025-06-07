bits 32
segment code public code use32
global _cat_ext

_cat_ext:
    ;int cat_ext(string, length, destinaton)
    ;returneaza lugimea sirului de cifre concatenate
    
    urm:
    push ebx
    mov ebx, esi
    
    
    mov ecx, [ebp + 8]
    mov esi, [ebp + 12]
    mov edi, [ebp + 4]
    add edi, ebx
    jecxz fin
    
    parc1:
        cmp [esi], byte'0'
        jb no_digit1
        cmp [esi], byte'9'
        ja no_digit1
            mov al, [esi]
            stosb
            inc edx
        no_digit1:
        inc esi
    loop parc1
    
    fin:
    
    mov eax, edx
    
    mov esp, ebp
    pop ebp
       
    ret
   