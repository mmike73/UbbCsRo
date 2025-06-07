bits 32

global start

extern exit

import exit msvcrt.dll

segment data use32 class=data
;c+(a*a-b+7)/(2+a)
a db 5
b dd 7
c dq 30
;30 + 25 / 7 = 33
segment code use32 class=code

start:

mov al, [a]
mov bl, [a]
imul bl
cwde

sub eax, dword[b]
add eax, 7

push eax

mov al, [a]
add al, 2
cbw

mov bx, ax

pop ax
pop dx

idiv bx


cwde
cdq

mov ebx, dword[c]
mov ecx, dword[c +4]

add eax, ebx
adc edx, ecx

push dword 0
call [exit]