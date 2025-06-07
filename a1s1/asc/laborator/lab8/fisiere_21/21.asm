bits 32
global start
extern exit, fopen, fclose, fread, fprintf

import exit msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll
import fread msvcrt.dll
import fprintf msvcrt.dll

segment data use32 class=data

    nume_fisier db "cifre.txt", 0
    mod_acces db "r", 0
    mod_acces_w db "w", 0
    descriptor dd 0
    desc_w dd 0
    siz dd 1
    count dd 100
    len dd 0
    s times 101 db 0
    format db "%s", 0

segment code use32 class=code

start:
    push mod_acces
    push nume_fisier
    call [fopen]
    add esp, 4 * 2
    
    mov [descriptor], eax
    
    push dword [descriptor]
    push dword [count]
    push dword [siz]
    push s
    call [fread]
    add esp, 4 * 4
    
    mov esi, 0
    mov ecx, eax
    
    parc:
        mov al, [s + esi]
        cmp al, '0'
        jb cont
        cmp al, '9'
        ja cont
        push esi
        add esi, 1
        and esi, 1
        pop esi
        jz cont
            mov [s + esi], byte 'X'
            jmp cont

        cont:
        inc esi    
    loop parc
    
    push mod_acces_w
    push nume_fisier
    call [fopen]
    add esp, 4 * 2
    
    mov [desc_w], eax
    
    push s
    push format
    push dword [desc_w]
    call [fprintf]
    add esp, 3
    
    push dword[desc_w]
    call [fclose]
    add esp, 4
    
    push dword[descriptor]
    call [fclose]
    add esp, 4
    
    push dword 0
    call [exit]
    