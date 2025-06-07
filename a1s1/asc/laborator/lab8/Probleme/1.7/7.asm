bits 32
global start

extern printf, exit
import printf msvcrt.dll
import exit msvcrt.dll

segment data use32 class=data
    
    a dd 180
    b dw 50
    format db "<%d> mod <%d> = <%d>", 0
    
segment code use32 class=code
start:
    mov eax, [a]
    cdq
    mov ebx, 0
    mov bx, [b]
    cwde
    
    div ebx
    
    push edx
    push ebx
    push dword[a]
    push format
    call [printf]
    add esp, 4 * 2
    
    push dword 0
    call [exit]