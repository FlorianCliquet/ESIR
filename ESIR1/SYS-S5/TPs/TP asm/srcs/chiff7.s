section .data
    prompt_message db "Enter the string to be encrypted/decrypted:", 0xA
    prompt_message_len equ $-prompt_message

    key_prompt_message db "Enter the key:", 0xA
    key_prompt_message_len equ $-key_prompt_message

    result_message db "The encrypted/decrypted message is:", 0xA
    result_message_len equ $-result_message

section .bss
    buffer resb 100         ; tampon pour l'entrée utilisateur (limité à 100 caractères)
    key_buffer resb 100      ; tampon pour la clé (limité à 100 caractères)
    result resb 101          ; stockage pour le résultat (taille maximale 100 caractères + 1 pour le retour à la ligne)
    key_length resb 1        ; stockage pour la longueur de la clé

section .text
    global _start

_start:
    ; Afficher le message de demande d'entrée de la chaîne
    mov eax, 4                  ; syscall pour sys_write
    mov ebx, 1                  ; écrire sur stdout (file descriptor 1)
    mov ecx, prompt_message      ; pointeur vers le message
    mov edx, prompt_message_len  ; longueur du message
    int 0x80

    ; Lire la chaîne de caractères depuis l'entrée standard
    mov eax, 3                ; syscall number pour sys_read (3 dans Linux 32 bits)
    mov ebx, 0                ; lire depuis stdin (file descriptor 0)
    mov ecx, buffer           ; buffer de destination
    mov edx, 100              ; nombre maximal d'octets à lire
    int 0x80

    ; Calculer la longueur de la chaîne entrée
    mov ecx, eax              ; eax contient le nombre de caractères lus
    dec ecx                   ; enlever 1 à ecx pour ignorer le newline (retour à la ligne)
    mov ebp, ecx              ; sauvegarder la longueur de la chaîne dans ebp

    ; Afficher le message de demande d'entrée de la clé
    mov eax, 4                  ; syscall pour sys_write
    mov ebx, 1                  ; écrire sur stdout (file descriptor 1)
    mov ecx, key_prompt_message  ; pointeur vers le message
    mov edx, key_prompt_message_len  ; longueur du message
    int 0x80

    ; Lire la clé de chiffrement depuis l'entrée standard
    mov eax, 3                ; syscall number pour sys_read (3 dans Linux 32 bits)
    mov ebx, 0                ; lire depuis stdin (file descriptor 0)
    mov ecx, key_buffer       ; buffer de destination pour la clé
    mov edx, 100              ; nombre maximal d'octets à lire
    int 0x80

    ; Calculer la longueur de la clé entrée
    mov esi, eax              ; eax contient le nombre de caractères lus pour la clé
    dec esi                   ; enlever 1 à esi pour ignorer le newline (retour à la ligne)
    mov [key_length], esi      ; stocker la longueur de la clé dans key_length

    ; Initialiser les registres pour le chiffrement
    mov esi, buffer           ; pointeur vers la chaîne d'entrée
    mov edi, result           ; pointeur vers le résultat
    xor edx, edx              ; index pour la clé de chiffrement

    ; Restaurer la longueur de la chaîne à chiffrer
    mov ecx, ebp              ; restaurer la longueur de la chaîne d'entrée depuis ebp

next_char:
    cmp ecx, 0                ; vérifier si on a fini de parcourir la chaîne à chiffrer
    jle done

    lodsb                     ; charger le prochain caractère du buffer dans AL
    cmp al, 10                ; ignorer newline
    je store_char

    cmp al, 'A'
    jl store_char             ; stocker et ignorer les non-lettres
    cmp al, 'Z'
    jg store_char

    ; Calculer l'index de la clé actuelle
    mov bl, [key_buffer + edx] ; charger la clé actuelle depuis key_buffer
    sub bl, 'A'                 ; convertir la clé en index 0-25
    add edx, 1                  ; passer à la clé suivante
    cmp edx, [key_length]       ; vérifier si on a dépassé la longueur de la clé entrée
    jb continue_loop            ; continuer si l'index est valide
    xor edx, edx                ; réinitialiser l'indice si on dépasse la longueur

continue_loop:
    sub al, 'A'                 ; convertir la lettre en index 0-25
    sub bl, al                  ; appliquer le chiffrement
    js adjust                   ; si négatif, ajuster en ajoutant 26
    mov al, bl
    jmp convert

adjust:
    add bl, 26                  ; ajuster en ajoutant 26 si le résultat est négatif
    mov al, bl

convert:
    add al, 'A'                 ; reconvertir en ASCII

store_char:
    stosb                       ; stocker le caractère dans [edi]
    dec ecx                     ; décrémenter ecx pour la boucle
    jmp next_char

done:
    ; Ajouter un saut de ligne à la fin du texte chiffré
    mov byte [edi], 0xA         ; ajouter '\n' à la fin du résultat
    inc edi                     ; incrémenter edi pour prendre en compte le saut de ligne

    ; Afficher le message avant le résultat
    mov eax, 4                  ; syscall pour write
    mov ebx, 1                  ; file descriptor (stdout)
    mov ecx, result_message      ; pointeur vers le message
    mov edx, result_message_len  ; longueur du message
    int 0x80

    ; Calculer la longueur du résultat
    mov eax, edi                ; pointeur actuel de la destination
    sub eax, result             ; calculer la longueur du résultat
    mov edx, eax                ; sauvegarder la longueur dans edx

    ; Impression du résultat
    mov eax, 4                  ; syscall pour write
    mov ebx, 1                  ; file descriptor (stdout)
    mov ecx, result             ; pointeur vers le résultat
    int 0x80

    ; Sortie
    mov eax, 1                  ; syscall pour exit
    xor ebx, ebx                ; code de retour 0
    int 0x80
