bits 32
global start
extern exit, scanf, printf
import exit msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt.dll
segment data use32 class=data
    a db 0
    format_ra db "%x",0
    format_r db "Introdu un numar in baza 16: ", 0
    format_semn db "Cu semn: %d", 0
    format_fara_semn db "Fara semn: %u",0xa, 0
    
segment code use32 class=code

start:
    push format_r
    call [printf]
    add esp, 4 * 1
    
    push a
    push format_ra
    call [scanf]
    add esp, 4 * 2
    
    mov eax, 0
    mov al, [a]
    
    
    push eax
    push format_fara_semn
    call [printf]
    add esp, 4 * 1
    pop eax
    
    cbw
    cwde
    
    push eax
    push format_semn
    call [printf]
    add esp, 4 * 2
    
    push dword 0
    call [exit]
    
    