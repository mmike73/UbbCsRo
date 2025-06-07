bits 32
global start
extern scanf, printf, exit

import scanf msvcrt.dll
import printf msvcrt.dll
import exit msvcrt.dll

segment data use32 class=data

    a dd 0
    b dd 0
    format_r db "Introdu 2 numere in baza 16: ",0
    format_rab db "%x %x",0
    format_output_s db "suma = %x",0xa, 0
    format_output_d db "diferenta = %x",0

segment code use32 class=code
start:
    push format_r
    call [printf]
    add esp, 4
    
    push b
    push a
    push format_rab
    call [scanf]
    add esp, 4 * 3
    
    mov eax, 0
    mov ebx, 0
    mov ax, word[a]
    mov bx, word[b]
    add ax, bx
    
    push eax
    push format_output_s
    call [printf]
    add esp, 4 * 2
    
    mov eax, [a]
    mov ebx, [b]
    shr eax, 16
    shr ebx, 16
    add ax, bx
    
    push eax
    push format_output_d
    call [printf]
    add esp, 4 * 2
    
    push dword 0
    call [exit]