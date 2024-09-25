section .data
    message db "HELLO WORLD!", 10   ; message à chiffrer
    key_string db "DIANA"          ; chaîne de clés
    len_msg equ $-message - 5          ; longueur du message -5 pour les bytes en trop
    key_string_length equ $-key_string  ; longueur de la chaîne de clés

section .bss
    result resb len_msg            ; stockage pour le résultat

section .text
    global _start

_start:
    mov esi, message               ; pointeur vers le message
    mov edi, result                ; pointeur vers le résultat
    mov ecx, len_msg               ; longueur du message
    xor edx, edx                   ; index pour key_string

next_char:
    cmp ecx, 0                     ; vérifier si on a fini
    jle done

    lodsb                          ; charger le prochain caractère du message dans AL
    cmp al, 10                     ; ignorer newline
    je store_char

    cmp al, 'A'
    jl store_char                  ; stocker et ignorer les non-lettres
    cmp al, 'Z'
    jg store_char

    ; Calculer l'index de la clé actuelle
    mov bl, [key_string + edx]     ; charger la clé actuelle depuis key_string
    sub bl, 'A'                    ; convertir la clé en index 0-25
    add edx, 1                     ; passer à la clé suivante
    cmp edx, key_string_length      ; vérifier si on a dépassé la longueur de la chaîne
    jb continue_loop               ; continuer si l'index est valide
    xor edx, edx                   ; réinitialiser l'indice si on dépasse la longueur

continue_loop:
    sub al, 'A'                    ; convertir la lettre en index 0-25
    sub bl, al                     ; décalage (clé - lettre)
    js adjust                      ; si négatif, ajuster en ajoutant 26
    mov al, bl
    jmp convert

adjust:
    add bl, 26                     ; ajuster en ajoutant 26 si le résultat est négatif
    mov al, bl

convert:
    add al, 'A'                    ; reconvertir en ASCII

store_char:
    stosb                          ; stocker le caractère dans [edi]
    dec ecx                        ; décrémenter ecx pour la boucle
    jmp next_char

done:
    ; Impression du résultat
    mov eax, 4
    mov ebx, 1
    mov ecx, result
    mov edx, len_msg
    int 0x80

    ; Sortie
    mov eax, 1
    xor ebx, ebx
    int 0x80

