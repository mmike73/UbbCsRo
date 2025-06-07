bits 32
global start
extern exit, printf, scanf, val_max, convert_b16
import exit msvcrt.dll
import printf msvcrt.dll
import scanf msvcrt.dll

segment data use32 class=data

    a resb 101 
    num resw 101
    ind dd 0
    format_inp db "Introdu numerele: ", 0
    format db "%s", 0
    format_d db "Numarul maxim in baza 16 este: %x", 0xA, 0
    maximumul dd 0


segment code use32 class=code



start:

    push format_inp
    call [printf]
    add esp, 4
    
    push a
    push format
    call [scanf]
    add esp, 4 * 2
    
    mov esi, a
    mov edi, a
    mov ebx, 0
    
    parc:
    cmp [edi], byte','
    
    jne digit
        dec edi
        
        mov ecx, edi
        sub ecx, esi
        inc ecx
        mov eax, 0
        push esi
        
        scrie_reg:
            mov dl, [esi]
            sub dl, byte '0'
            shl eax, 4
            add al, dl
            inc esi 
        loop scrie_reg
        call convert_b16
        pop esi
        add edi, 2
        mov esi, edi
        dec edi
        
        mov ebx, [ind]
        mov [num + ebx], ax
        inc dword[ind]
        inc dword[ind]
        
    digit:
    
    
    
    inc edi
    cmp [edi + 1], byte 0
    je gata
    jmp parc
    gata:
    
        
        mov ecx, edi
        sub ecx, esi
        inc ecx
        mov eax, 0
        push esi
        
        scrie_reg1:
            mov dl, [esi]
            sub dl, byte '0'
            shl eax, 4
            add al, dl
            inc esi 
        loop scrie_reg1
        call convert_b16
        pop esi
        add edi, 2
        mov esi, edi
        dec edi
        
        mov ebx, [ind]
        mov [num + ebx], ax
        inc dword[ind]
        inc dword[ind]
        
    mov ecx, [ind]
    mov ebx, num
    call val_max
    
    mov [maximumul], eax
    
    push eax
    push format_d
    call [printf]
    add esp, 4 * 2
    
    push dword 0
    call [exit]
    
    
    
    
    

    
    
