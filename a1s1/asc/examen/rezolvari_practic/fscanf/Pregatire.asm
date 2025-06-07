bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, scanf, fopen, fclose               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
import fopen msvcrt.dll
import fclose msvcrt.dll
import scanf msvcrt.dll

; our data is declared here (the variables needed by our program)
segment data use32 class=data
nume_fisier times 100 db 0
format_1 db "%s", 0
format_2 db "%d", 0
format_3 db "%c", 0
n dd 0
m dd 0
; our code starts here
segment code use32 class=code
    start:
        push m 
        push format_3
        call [scanf]
        add esp, 8
        push nume_fisier
        push format_1
        call [scanf]
        add esp, 8
        
        push n
        push format_2
        call [scanf]
        add esp, 8
        
        
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
