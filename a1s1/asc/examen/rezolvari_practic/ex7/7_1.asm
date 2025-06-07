bits 32
global start

extern exit, fread, printf, fopen, fclose

import exit msvcrt.dll
import fread msvcrt.dll
import printf msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll

segment data use32 class=data

    nume_fisier db "text.txt",0
    mod_acces db "r",0
    descriptor dd 0
    cnt dd 101
    sz dd 1
    
    inp times 101 db 0
    len_txt dd 0
    
    propozitie times 101 db 0
    len_prop dd 0
    nr_cuv dd 0

    cuvant times 21 db 0
    len_cuv dd 0

    primul_rev times 21 db 0
    len_prim dd 0 
    pus dd 0
    
segment code use32 class=code



start:
    push mod_acces
    push nume_fisier
    call [fopen]
    add esp, 4 * 2
    
    mov dword[descriptor], eax
    
    push dword[descriptor]
    push dword[cnt]
    push dword[sz]
    push inp
    call [fread]
    add esp, 4 * 4
    
    mov esi, inp
    mov edi, inp
    
    parcurge_text:
        cmp edi, 0
        je parcurgere_terminata
        
        cmp byte[edi], '.'
        jne nu_propozitie
            
            
            push esi
            push edi
            
          
                
                mov ecx, eax
                mov edi, propozitie
                rep movsb
                
                mov dword[pus], 0
                mov dword[nr_cuv], 0
                
                mov ecx, 21
                mov al, 0
                mov edi, primul_rev
                rep movsb
                
                mov dword[len_prim], 0
                
                mov esi, propozitie
                mov edi, propozitie
                
                mov ecx, [len_prop]
                
                parcurge_propozitie:
                    cmp edi, ' '
                    jne nuc
                        mov eax, edi
                        sub eax, esi
                        
                        cmp eax, 1
                        je not_c
                        
                            inc dword[nr_cuv]
                            cmp dword[len_prim], 0
                            jne deja_pus
                                mov ecx, dword[len_prim]
                                push esi
                                push edi
                                
                                    mov edi, cuvant
                                    add edi, dword[len_cuv]
                                    mov esi, primul_rev
                                    
                                    copiaza:
                                        mov al, byte[edi]
                                        mov byte[esi], al
                                        inc esi
                                        dec edi
                                    loop copiaza
                                
                                pop edi
                                pop esi 
                            deja_pus:
                            
                        not_c:
                        mov esi, edi
                        inc esi
                         
                    nuc:
                    inc edi
                
                loop parcurge_propozitie
                
                
            
            pop edi
            pop esi
            
            
            mov esi, edi
            inc esi
    
        nu_propozitie:
        inc edi
    jmp parcurge_text
    parcurgere_terminata:
    
    push dword[descriptor]
    call [fclose]
    add esp, 4
    
    push dword 0
    call [exit]
    