bits 32
global start

extern exit, scanf, printf
import exit msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt.dll

segment data use32 class=data

    format db "Introdu un numar in baza 2:%s", 0
    format_d db "Cate numere doresti sa introduci?%d", 0
    format_octal db "Echivalentul sau in baza 8:%o", 0xA, 0
    n dd 0
    s times 32 db 0
    rez dd 0

segment code use32 class=code

start:
    push n
    push format_d
    call [scanf]
    add esp, 4 * 2
    
    mov ecx, [n]
    rd:
        push ecx
        push s
        push format
        call [scanf]
        add esp, 4 * 2
        
        
        mov ebx, 0
        cld
        mov ecx, 32
        mov esi, s
        
        load:
            lodsb
            
            cmp al, 0
            je gata
            sub al, 30h
            add bl, al
            rol ebx, 1
        
        loop load
        gata:
        ror ebx, 1
        
        
        mov [rez], ebx
        
        
        push dword[rez]
        push format_octal
        call [printf]
        add esp, 4 * 2
        
        pop ecx
        
    loop rd
    
    push dword 0
    call [exit]