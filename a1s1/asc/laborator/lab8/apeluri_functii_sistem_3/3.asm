bits 32
global start
extern exit
extern scanf
extern printf
import exit msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt.dll

segment data use32 class=data
    a dw 4
    b dw 5
    result dw 0
    format_ask_for_a_b db "Introdu doua numere %d%d", 0
    format_result db "%d + %d = %d", 0
    
segment code use32 class=code
    start:
    
    ;se citeste a si b
    ;push dword b
    ;push dword a
    ;push dword format_ask_for_a_b
    
    ;call [scanf]
    
    ;add esp, 4 * 3
    
    ;result = a + b
    mov eax, 0
    mov ax, word[a]
    add ax, word[b]
    
    mov [result], ax
    
    ;se afiseaza a + b = result
    push eax
    mov eax, 0
    mov ax, [b]
    push eax
    mov eax, 0
    mov ax, [a]
    push eax
    push dword format_result
    
    call [printf]
    
    add esp, 4 * 4
    
    ;call [exit]
    push dword 0
    
    
    
    