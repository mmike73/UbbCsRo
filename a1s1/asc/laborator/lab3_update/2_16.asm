bits 32

global start

extern exit

import exit msvcrt.dll

segment data use32 class=data
;x/2+100*(a+b)-3/(c+d)+e*e
x dq 1000
a dw 2
c dw 4
b db 7
d db 9
e dd 5
;500 + 900  - 3 / 13 +  25 = 1425  = 591h
segment code use32 class=code

start:
;x / 2
mov eax, dword[x]
mov edx, dword[x + 4]

mov ebx, 2

div ebx

push eax ;x / 2

;100 * ( a + b)
mov al, [b]
cbw
add ax, [a]

mov bx, 100

mul bx

push dx ;100 * ( a + b)
push ax

;3 / ( c + d)

mov al, [d]
cbw
add ax, [c]

mov bx, ax
mov ax, 3
cwd
div bx

push ax ;3 / (c + d)

mov eax, [e]
mul dword[e]

mov ebx, eax
mov ecx, edx

pop ax
cwde
cdq
add ebx, eax
adc ecx, edx

pop eax
cdq

add ebx, eax
adc ecx, ebx

pop eax

add eax, ebx
adc edx, ecx


push dword 0
call [exit]
