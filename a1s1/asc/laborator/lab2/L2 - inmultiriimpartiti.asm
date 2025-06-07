bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    
    a DB 4
    b DB 8
    c DB 3
    d DW 5bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...

; our code starts here
segment code use32 class=code
    start:
        ; ...
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack

    
    doi DB 2

; our code starts here
segment code use32 class=code
    start:
        ;1
        mov AL, [a]
        add AL, [b]
        sub AL, [c]
        mov DH, 2
        mul DH
        add AX, [d]
        sub AX, 5
        mov DX, [d]
        mul DX
        
          
        ;16
        mov AL, [a]
        add AL, [b]
        mov AH, 0
        mov DL, [doi] 
        div DL
        mov DL, AL
        mov CL, 10
        mov AL, [a]
        mov AH, 0
        mov CH, [c]
        div CH
        sub CL, AL
        add DL, CL
        mov AL, [b]
        mov AH, 0
        mov DH, 4
        div DH
        add DL, AL
        mov AL, DL
        
        
                
        
      
        
        
        
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
