bits 32
global start
extern scanf, printf, exit, convert
import scanf msvcrt.dll
import printf msvcrt.dll
import exit msvcrt.dll

segment data use32 class=data

    format db "Introdu numere si caracterul 'z' atunci cand dorest sa inchei programul:", 0xa, 0
    format_s db "%s", 0
    format_h db "%x",0xa, 0
    s times 32 db 0

segment code use32 class=code

start:
    push format
    call [printf]
    add esp, 4 * 1
    
    lp:
        push s
        push format_s
        call [scanf]
        add esp, 4 * 2
        
        cmp byte[s], 'z'
        je gata
        
        push s
        call convert
        
        
        push eax
        push format_h
        call [printf]
        add esp, 4 * 2
    
    jmp lp
    gata:
    
    
    push dword 0
    call [exit]