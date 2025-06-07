bits 32
global start

extern exit, scanf, printf, fopen, fclose, fread
import exit msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll
import fread msvcrt.dll

segment data use32 class=data

    nume_fisier db "caracter_special.txt", 0
    descriptor_fisier dd 0
    sizee dd 1
    count dd 100
    mod_acces db "r", 0
    s times 101 db 0
    fr times 101 db 0
    len dd 0
    maxim dd 0
    cmax db 0
    format db "Caracterul special %c a fost folost de %d ori.", 0

segment code use32 class=code
start:
    push mod_acces
    push nume_fisier
    call [fopen]
    add esp, 4 * 2
    mov [descriptor_fisier], eax
    
    
    
    ;fread(adresa, size, count, file stream)
    push dword[descriptor_fisier]
    push dword[count]
    push dword[sizee]
    push s
    call [fread]
    add esp, 4 * 4
    
    mov [len], eax
    mov ecx, [len]
    mov esi, 0
    lp:
        mov al, [s + esi]
        cmp al, 'A'
        jb literaa
            cmp al, 'z'
            ja literaa
            
            cmp al, 'a'
            jae litera
            cmp al, 'Z'
            jbe litera
            
        literaa:
            mov dl, [fr + esi]
            cmp dl, 1
            je litera
            mov edx, 1
            push esi
                
                inc esi
                li:
                    cmp al, [s + esi]
                    jne not_eq
                        inc edx
                        mov byte[fr + esi], 1
                    not_eq:
                    inc esi
                    cmp esi, [len]
                    jae gata
                jmp li
            gata:
            
            cmp edx, [maxim]
            jbe nope
                mov [maxim], edx
                mov [cmax], al
            nope:            
            pop esi
        litera:
        inc esi
    loop lp
    
    push dword [maxim]
    push dword [cmax]
    push format
    call [printf]
    add esp, 4 * 3
    
    push dword 0
    call [exit]
    
    