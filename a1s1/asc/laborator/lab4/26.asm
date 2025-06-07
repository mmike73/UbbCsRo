bits 32

global start

extern exit

import exit msvcrt.dll

segment data use32 class=data

    Q resd 1
    R dd 10110111010101011110110001010110b
    T dd 11011101011110100010101001011110b
    RXORT resd 1
    
    ;R:10110111010101011110110001010110b
    ;T:11011101011110100010101001011110b
    ;X:01101010001011111100011000001000b
    ;Q:1100010|000101111110001100|0001010b
    ;Q:   c    4   2   f   c   6    0   a
segment code use32 class=code

start:

    mov eax,[T]
    ;plasez bitii 10-16 in 0-6
    shl eax, 16
    shr eax, 26
    
    mov ebx, 0
    mov ebx, eax
    
    mov eax, [R]
    ;elimin zerorizez toti bitii care sunt in afara 7-20
    shr eax, 5
    shl eax, 25
    ;se mai poate face and cu un sir care sa aiba 0 unde vreau sa elimin si 1 in rest - unde vreau sa pastrez?
    mov ecx, 0
    add ecx, eax
    
    mov eax, [R]
    
    mov edx, 0
    mov edx, [T]
    xor eax, edx
    ;mut bitii 5-11 in 25-31
    shr eax, 7
    shl eax, 14
    shr eax, 7
    
    
    add eax, ebx
    add eax, ecx
    push dword 0
    call [exit]
    