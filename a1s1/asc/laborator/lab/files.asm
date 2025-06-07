bits 32
global start 
extern exit

extern fopen
extern fread
extern printf
extern fclose
import exit msvcrt.dll
import fopen msvcrt.dll
import fread msvcrt.dll
import printf msvcrt.dll
import fclose msvcrt.dll

segment data use32 class=data

    nume_fisier db "input.txt", 0
    mod_acces db "r", 0
    format db "", 0
    descriptor dd 0
    count dd 100
    dimensiune dd 1
    lungime_sir dd 0
    text resb 100
    warning db "Nu exista cifre in textul dat", 0
    rez db "Cea mai mare cifra din sirul de caractere este %c", 0
    
segment code use32 class=code

start:
    ;FILE * fopen
    push dword mod_acces
    push dword nume_fisier
    call [fopen]
    add esp, 4 * 2
    
    cmp eax, 0
    je final
    
    mov [descriptor], eax
    
    ;int fread
    
    push dword [descriptor]
    push dword [count]
    push dword [dimensiune]
    push dword text
    
    call [fread]
    add esp, 4 * 4
    
    mov [lungime_sir], eax
    mov ecx, [lungime_sir]
    mov ebx, 0
    
    cifmax:
        mov al, [text + ecx]
        
        cmp al, '0'
        jb nu_e_cif
            
            cmp al, '9'
            ja nu_e_cif
            
            cmp al, bl
            jbe nu_e_cif
                mov bl, al         
        nu_e_cif:
    loop cifmax
    
    cmp ebx, 0
        jne sunt_cifre
            push warning
            
            
            call [printf]
            add ebp, 4 * 1
        sunt_cifre:
        
        
        push ebx
        push rez
        call [printf]
        add esp, 4 * 1

    final:
    
    push dword 0
    call [exit]
  
    