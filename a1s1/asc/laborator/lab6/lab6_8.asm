bits 32
global start
extern exit
import exit msvcrt.dll

segment data use32 class=data

    s dd 12345678h, 1a2c3c4dh, 98fcdc76h
    len equ ($ - s) / 4
    d resb 3
    hex db 10

segment code use32 class=code

start:

    mov esi, s + 2
    mov ecx, len
    jecxz final
    cld
    sir:
        lodsd  
        
        push ecx
        push esi
        
    conv_to_base_10:
        mov bl, al
        xor eax, eax
        mov al, bl
        xor edx, edx
        xor ecx, ecx
        
    
    convert_digit:
        div byte [hex]
        add dl, '0'
        push dx
        inc ecx
        test eax, eax
    jnz convert_digit
        
    pop_digits
        pop dx
            mov [ecx + edx - 1], dl
        loop pop_digits
        
        pop esi
        pop ecx
    loop sir
    
    final:
    
    
    ret
        
        
    

push dword 0
call [exit]

