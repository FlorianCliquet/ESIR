section .data
    message db "HELLO WORLD", 10  ; message à chiffrer (ajout d'un newline explicite)
    len_msg equ $-message     ; longueur du message

section .bss
    result resb len_msg       ; espace pour stocker le résultat

section .text
    global _start

_start:
    mov esi, message          ; pointeur vers le message
    mov edi, result           ; pointeur vers le résultat
    mov ecx, len_msg          ; longueur du message

next_char:
    cmp ecx, 0                ; vérifier si nous avons traité tous les caractères
    jle done                  ; si oui, on termine

    lodsb                     ; charger le prochain caractère de [esi] dans al
    cmp al, 10                ; vérifier si c'est un newline (0xA)
    je store_char             ; si c'est un newline, l'enregistrer tel quel

    cmp al, 'A'
    jl store_char                 ; ignorer si en-dessous de 'A'
    cmp al, 'Z'
    jg store_char                 ; ignorer si au-dessus de 'Z'

    sub al, 'A'               ; convertir en index 0-25
    mov bl, 25                ; bl = 25 pour le calcul de la symétrie
    sub bl, al                ; 25 - position
    add bl, 'A'               ; reconvertir en ASCII
    mov al, bl                ; remettre la nouvelle lettre dans al

store_char:
    stosb                     ; stocker le caractère dans [edi]

ignore:
    loop next_char            ; diminuer ecx et sauter à next_char

done:
    ; Appeler la fonction pour imprimer le message chiffré
    mov eax, 4                ; syscall numéro pour write
    mov ebx, 1                ; stdout
    mov ecx, result           ; le message chiffré
    mov edx, len_msg          ; taille du message
    int 0x80                  ; appel système

    ; Sortir du programme
    mov eax, 1                ; syscall numéro pour exit
    xor ebx, ebx              ; code de retour
    int 0x80

