bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a DB 9
    b DB 5
    c DB 4
    d DB 8
    e DW 10
    f DW 7
    g DW 9
    h DW 11

; our code starts here
segment code use32 class=code
    start:
        
        ;1
        mov AL, [a]
        sub AL, [b]
        mov DL, 4
        mul DL
        mov DL, [c]
        div DL
        
        ;16
        mov AX, 0
        mov AL, [a]
        mov DL, [a]
        mul DL
        mov DX, [e]
        add DX, [f]
        sub AX, DX
        
        
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
