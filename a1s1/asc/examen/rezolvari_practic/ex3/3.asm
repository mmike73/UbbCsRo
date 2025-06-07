bits 32
global start
extern exit, fread, fopen, fclose, printf
import exit msvcrt.dll
import fread msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll
import printf msvcrt.dll

segment data use32 class=data

    nume_fisier db "cifre.txt",0
    mod_acces db "r", 0
    
    ct dd 100
    sz dd 1
    
    descriptor dd 0
    
    format_read db "%s", 0
    format_print db "%x - %d", 0xa, 0
    
    arr times 101 db 0
    len dd 0

segment code use32 class=code
start:
    push mod_acces
    push nume_fisier
    call [fopen]
    add esp, 4 * 2
    
    mov [descriptor], eax
    
    push dword [descriptor]
    push dword [ct]
    push dword [sz]
    push arr
    call [fread]
    
    mov [len], eax
    
    mov ecx, [len]
    mov esi, arr
    mov eax, 0
    
    parc:
        push ecx
        lodsb
        cmp al, " "
        je nc
            cmp al, '9'
            ja subA
            sub al, '0'
            jmp ove
            subA:
            sub al, 'A'
            add al, 0ah
            ove:
            
            mov edx, 0
            push eax
            cnt:
                mov ebx, 1
                and ebx, eax
                add edx, ebx
                shr eax, 1
                
            cmp eax, 0
            je gata
            jmp cnt 
            gata:
            pop eax
            push edx
            push eax
            push format_print
            call [printf]
            add esp, 4 * 3
        nc:
        pop ecx
    loop parc
    
    push dword[descriptor]
    call [fclose]
    add esp, 4
    
    push dword 0
    call [exit]