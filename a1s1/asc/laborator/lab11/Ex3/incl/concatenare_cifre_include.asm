%ifndef _CAT
%define _CAT

cat_ext:
    ;int cat_ext(string, length, destinaton)
    ;returneaza lugimea sirului de cifre concatenate
    
    urm:
    
    mov ecx, [esp + 8]
    mov esi, [esp + 12]
    mov edi, [esp + 4]
    add edi, edx
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
    
    ret 4 * 3
   
%endif