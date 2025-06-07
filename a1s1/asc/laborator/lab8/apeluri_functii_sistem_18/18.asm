bits 32
global start

extern printf, scanf, exit
import printf msvcrt.dll
import scanf msvcrt.dll
import exit msvcrt.dll

segment data use32 class=data
    
    ab10 dd 0
    ab16 dd 0
    rez dd 0
    mesaj1 db "Introdu un numar in baza 10 si unul in baza 16: ", 0
    format1 db "%d %x"
    format2 db "Numarul de cifre 1 in scrierea binara a sumei este: %d", 0
    rez_char resb 32
    
segment code use32 class=code
    start:
    
    push mesaj1
    call [printf]
    add esp, 4
    
    push dword ab10
    push dword ab16
    push dword format1
    call [scanf]
    add esp, 4 * 3
    
    
    mov eax, 0
    mov eax, [ab10]
    add eax, [ab16]
    
    mov [rez], eax
    
    jmp convert_to_binary
    
    convert_to_binary:
        mov ecx, 32
        mov ebx, 2
        mov eax, [rez]
        cdq
        mov edi, 0
        mov esi, 0
        cv:
            cmp eax, 0
            jne nu_e_zero
                mov ecx, 1
            nu_e_zero:
            div ebx
            mov [rez_char + edi], dl
            cmp dl, byte 1
            jne not_eq
                inc esi
            not_eq:
            inc edi
            cdq
            
        loop cv
        
        push esi
        push format2
        call [printf]
        add esp, 4 * 2 
    
    push dword 0
    call [exit]
    
    
    