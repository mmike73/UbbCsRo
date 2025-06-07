bits 32
global start
extern exit, fread, printf, fopen, fclose

import exit msvcrt.dll
import fread msvcrt.dll
import printf msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll

segment data use32 class-data

    nume_fisier db "text.txt", 0
    mod_acces db "r", 0
    descriptor dd 0
    count dd 150
    sz dd 1
    
    brut times 151 db 0
    
    pus dd 0
    len dd 0
    
    prim_invers times 20 db 0
    cv times 20 db 0
    cnt_prim dd 0
    
    cnt_cuvinte dd 0
    propozitie times 51 db 0

segment code use32 class=code
start:
    push mod_acces
    push nume_fisier
    call [fopen]
    add esp, 4 * 2
    
    mov [descriptor], eax
    
    push dword[descriptor]
    push dword[count]
    push dword[sz]
    push brut
    call [fread]
    add esp, 4 * 4
    
    mov esi, brut
    mov edi, brut
    parc:
        cmp byte[edi], '.'
        jne nope
            
            push esi
            push edi
            
            elim_sp:
                cmp [esi], byte' '
                jne eltd
                inc esi
            jmp elim_sp
            eltd:
                
            mov eax, edi
            sub eax, esi
            inc eax
            mov [len], eax
            
            
            
            ;copiaza propozitia separat
            mov ecx, eax
            mov edi, propozitie
            rep movsb
            
            
            mov esi, propozitie
            mov edi, propozitie
            mov edx, 0
            mov [cnt_prim], dword 0
            
     
            mov [pus], dword 0
            prc:
                cmp byte[edi], '.'
                je gataa
                cmp byte[edi], ' '
                jne litera
                    mov eax, edi
                    sub eax, esi
                    cmp eax, 0
                    je nex
                        inc edx
                    nex:
                    
                    push ecx
                    push esi
                    push edi
                    
                        mov ecx, eax
                        mov edi, cv
                        rep movsb
                        
                        cmp dword[pus], 0
                        jne deja_pus
                            mov ecx, eax
                            mov [cnt_prim], eax
                            inc ecx
                            mov edi, prim_invers
                            mov esi, cv
                            add esi, eax
                            cpy:
                                mov al, [esi]
                                dec esi
                                mov [edi], al
                                inc edi
                            loop cpy
                            
                            mov dword[pus], 1
                        deja_pus:
                        
                        
                       
                        
                    
                    pop edi
                    pop esi
                    pop ecx  
                    
                    mov esi, edi
                    inc esi
                litera:
            cmp [esi], byte'.'
            je gataa
            inc edi
            jmp prc
            gataa:
            
                mov eax, edi
                sub eax, esi
                cmp eax, 0
                je ney
                inc edx
                ney:
                
                push ecx
                push esi
                push edi
                    
                        mov ecx, eax
                        mov edi, cv
                        rep movsb
                
                pop edi
                pop esi
                pop ecx
               
                
            pop edi
            pop esi
            
            add esi, [len]
            inc edi
            
        nope:
        inc edi
    
    cmp byte[edi], 0
    je gata
    jmp parc
    gata:
    
    push dword[descriptor]
    call [fclose]
    add esp, 4 * 1
    
    push dword 0
    call [exit]
    
    
   
   