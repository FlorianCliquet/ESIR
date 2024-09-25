section .data
    msg db '0', 0x0a, 0x00       ; Message contenant '0', saut de ligne, et terminateur nul
    msg2 db '1', '0', 0x0a, 0x00 ; Message contenant '10', saut de ligne, et terminateur nul

section .text
    global _start

_start:
    mov ecx, msg                 ; Charger l'adresse de msg dans ecx
    mov byte [msg], '0'           ; Initialiser le premier caractère à '0'
    mov byte [msg+1], 0x0a        ; Ajouter saut de ligne après chaque caractère

print_loop:
    call print_single             ; Appeler la fonction pour imprimer un chiffre
    call sleep
    inc byte [msg]                ; Incrémenter le premier caractère (par exemple, '0' -> '1')
    cmp byte [msg], '9'           ; Comparer avec '9'
    jbe print_loop                ; Si <= '9', continuer la boucle d'impression

    ; Maintenant imprimer les nombres de 10 à 20
    mov ecx, msg2                 ; Charger l'adresse de msg2 dans ecx
    mov byte [msg2], '1'          ; Initialiser le premier caractère à '1'
    mov byte [msg2+1], '0'        ; Initialiser le deuxième caractère à '0'

print_two_digit_loop:
    call print_double             ; Appeler la fonction pour imprimer un nombre à deux chiffres
    call sleep
    inc byte [msg2+1]             ; Incrémenter le deuxième chiffre
    cmp byte [msg2+1], '9'        ; Si le deuxième chiffre est 9, passer à la décennie suivante
    jbe continue_two_digit        ; Si <= '9', continuer la boucle
    inc byte [msg2]               ; Incrémenter le premier chiffre ('1' -> '2')
    mov byte [msg2+1], '0'        ; Réinitialiser le deuxième chiffre à '0'

continue_two_digit:
    cmp byte [msg2], '2'          ; Arrêter si le premier chiffre est '2' et le deuxième est '0'
    je done                       ; Fin de la boucle à '20'
    jmp print_two_digit_loop      ; Répéter pour les nombres jusqu'à '20'

sleep:
    mov eax, 162                  ; Appel système pour nanosleep
    lea ebx, [esp-8]              ; Charger l'adresse de l'argument (struct timespec)
    mov dword [ebx], 0            ; Temps en secondes
    mov dword [ebx+4], 500000000  ; Temps en nanosecondes (0,5 seconde)
    int 0x80                      ; Appel à l'interruption pour nanosleep
    ret

done:
    call exit                     ; Appeler la fonction d'arrêt

; Fonction d'impression pour les chiffres uniques
print_single:
    mov eax, 4                    ; Numéro de l'appel système sys_write (4)
    mov ebx, 1                    ; Descripteur de fichier pour stdout (1)
    mov edx, 2                    ; Nombre d'octets à écrire (chiffre + saut de ligne)
    int 0x80                      ; Interruption pour invoquer l'appel système
    ret                           ; Retour à l'appelant

; Fonction d'impression pour deux chiffres
print_double:
    mov eax, 4                    ; Numéro de l'appel système sys_write (4)
    mov ebx, 1                    ; Descripteur de fichier pour stdout (1)
    mov edx, 3                    ; Nombre d'octets à écrire (deux chiffres + saut de ligne)
    int 0x80                      ; Interruption pour invoquer l'appel système
    ret                           ; Retour à l'appelant

; Fonction d'arrêt du programme
exit:
    mov eax, 1                    ; Numéro de l'appel système sys_exit (1)
    xor ebx, ebx                  ; Code de retour 0 (succès)
    int 0x80                      ; Interruption pour invoquer l'appel système

