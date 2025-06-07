bits 32
segment code use32 public code
global val_max
global convert_b16

val_max:
    mov edx, 0
    
    maxim:
        
        mov ax, [ebx + ecx - 2]
        cmp dx, ax
        jae nup
            mov dx, ax
            
        nup:
        dec ecx
    loop maxim
    
    mov eax, edx
    
    ret
    
    
convert_b16:
    push ecx
    mov ebx, 0
    add bl, al
    
    push eax
        shr eax, 4
        shl eax, 4
        sub bl, al
    pop eax
    
    shr eax, 4
    
    push eax
    
    mov dl, 10
    
    mov ecx, eax
    shr ecx, 4
    shl ecx, 4
    sub al, cl
    
    mul dl
    add bx, ax
    
    pop eax
    
    shr eax, 4
    
    push eax
    
    mov dl, 100
    
    mul dl
    add bx, ax
    
    pop eax
    
    pop ecx
    
    mov eax, ebx
    ret