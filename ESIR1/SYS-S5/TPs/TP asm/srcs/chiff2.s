section .data
    message db "HELLO WORLD", 10
    key db 'D'
    len_msg equ $-message - 1

section .bss
    result resb len_msg

section .text
    global _start

_start:
    mov esi, message     ; pointeur vers le message
    mov edi, result      ; pointeur vers le résultat
    mov ecx, len_msg     ; longueur du message
    movzx ebx, byte [key]
    sub bl, 'A'          ; calculer le décalage de la clé (3 pour 'D')

next_char:
    cmp ecx, 0           ; vérifier si on a fini
    jle done

    lodsb                ; charger le prochain caractère
    cmp al, 10           ; ignorer newline
    je store_char

    cmp al, 'A'
    jl store_char            ; ignorer les non-lettres
    cmp al, 'Z'
    jg store_char

    sub al, 'A'          ; convertir en index 0-25
    mov dl, bl           ; sauvegarder le décalage de la clé dans dl
    sub dl, al           ; décalage - position (dl -= al)
    js adjust            ; si négatif, ajuster en ajoutant 26
    mov al, dl           ; le résultat du décalage est maintenant dans al
    jmp convert

adjust:
    add dl, 26           ; ajuster en ajoutant 26 si négatif
    mov al, dl           ; mettre le résultat dans al

convert:
    add al, 'A'          ; reconvertir en ASCII

store_char:
    stosb                ; stocker le caractère dans [edi]

ignore:
    loop next_char

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

