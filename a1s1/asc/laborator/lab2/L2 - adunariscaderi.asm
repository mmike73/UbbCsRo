bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    c DB 7
    a DB 3
    b DB 6
    d DB 4
    
    a1 DW 4
    b1 DW 6
    c1 DW 1
    d1 DW 3

; our code starts here
segment code use32 class=code
    start:
        ;adunari, scader, vqriabile bytes
        ;1
        mov AL, [c]
        mov DL, [a]
        add DL, [d]
        sub AL, DL
        mov DL, [b]
        add DL, [d]
        add AL, DL
        
        ;16
        mov AL, [a]
        add AL, 13
        sub AL, [c]
        add AL, [d]
        sub AL, 7
        add AL, [b]
        
        
        ;a1, b1, c1, d1 - word
        ;1
        mov AL, [c1]
        add AL, [b1]
        add AL, [a1]
        mov DL, [d1]
        add DL, [d1]
        sub AL, DL
        
        ;16
        mov AL, [a1]
        add AL, [b1]
        add AL, [b1]
        mov DL, [c1]
        sub DL, [d1]
        add AL, DL
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
