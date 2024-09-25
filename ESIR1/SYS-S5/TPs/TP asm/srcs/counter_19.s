section .data
    msg db '0', 0x0a, 0x00       ; Define the message with '0', newline, and null terminator
    msg2 db '1', '0', 0x0a, 0x00 ; Define the message with '10', newline, and null terminator

section .text
    global _start

_start:
    mov ecx, msg                 ; Load the address of msg into ecx
    mov byte [msg], '0'           ; Initialize the first character as '0'
    mov byte [msg+1], 0x0a        ; Add newline after each character

print_loop:
    call print_single             ; Call the function to print a single digit
    inc byte [msg]                ; Increment the first character (e.g., '0' -> '1')
    cmp byte [msg], '9'           ; Compare with '9'
    jbe print_loop                ; If it's <= '9', keep printing

    ; Now print numbers from 10 to 20
    mov ecx, msg2                 ; Load the address of msg2 into ecx
    mov byte [msg2], '1'          ; Initialize the first character as '1'
    mov byte [msg2+1], '0'        ; Initialize the second character as '0'

print_two_digit_loop:
    call print_double             ; Call the function to print a two-digit number
    inc byte [msg2+1]             ; Increment the second digit
    cmp byte [msg2+1], '9'        ; If the second digit is 9, move to the next decade
    jbe continue_two_digit        ; If less than or equal to '9', continue loop
    inc byte [msg2]               ; Increment the first digit ('1' -> '2')
    mov byte [msg2+1], '0'        ; Reset the second digit to '0'

continue_two_digit:
    cmp byte [msg2], '2'          ; Stop if the first digit is '2' and second digit is '0'
    je done                       ; End the loop when we hit '20'
    jmp print_two_digit_loop      ; Repeat for numbers up to '20'

done:
    call exit                     ; Call the exit function

; Print function for single digits
print_single:
    mov eax, 4                    ; sys_write system call number (4)
    mov ebx, 1                    ; File descriptor for stdout (1)
    mov edx, 2                    ; Number of bytes to write (digit + newline)
    int 0x80                      ; Interrupt to invoke system call
    ret                           ; Return to the caller

; Print function for two digits
print_double:
    mov eax, 4                    ; sys_write system call number (4)
    mov ebx, 1                    ; File descriptor for stdout (1)
    mov edx, 3                    ; Number of bytes to write (two digits + newline)
    int 0x80                      ; Interrupt to invoke system call
    ret                           ; Return to the caller

; Exit function to exit the program
exit:
    mov eax, 1                    ; sys_exit system call number (1)
    xor ebx, ebx                  ; Return code 0 (success)
    int 0x80                      ; Interrupt to invoke system call

