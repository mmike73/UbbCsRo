bits 32
global start

extern exit, printf

import exit msvcrt.dll
import printf msvcrt.dll

%include "concatenare_cifre_include.asm"

segment data use32 class=data

    str1 db "123", 0
    len1 dd $ - str1
    str2 db "21", 0
    len2 dd $ - str2
    len_rez dd 0
    rez resb 200 
    rez2 resb 200
    format db "%s ",0xA, 0

segment code use32 class=code

start:
    mov edx, 0
    push str1
    push dword[len1]
    push rez
    call cat_ext
    mov [len_rez], eax
    
    mov edx, [len_rez]
    push str2
    push dword[len2]
    push rez
    call cat_ext
    mov [len_rez], eax
    
    push rez
    push format
    call [printf]
    add esp, 4 * 2
   
    mov edx, 0
    mov [len_rez], dword 0
    
    
    push str2
    push dword[len2]
    push rez2
    call cat_ext
    mov [len_rez], eax
    
    mov edx, [len_rez]
    push str1
    push dword[len1]
    push rez2
    call cat_ext
    mov [len_rez], eax
    
    push rez2
    push format
    call [printf]
    add esp, 4 * 2
    
    
push dword 0

call [exit]