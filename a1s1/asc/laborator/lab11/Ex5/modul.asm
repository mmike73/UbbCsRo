bits 32
global lege

segment code use32 public code class

lege: 
    mov eax, [esp + 4]
    add eax, [esp + 8]
    sub eax, [esp + 12]
ret