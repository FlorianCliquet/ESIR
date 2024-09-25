section .data
    msg db '0', 0x0a, 0x00     ; Define the message with '0', newline, and null terminator

section .text
    global _start

_start:
    mov ecx, msg               ; Load the address of msg into ecx (for use with write)

repeat:
    call print                 ; Call the print function
    inc byte [msg]             ; Increment the first byte of msg (the character)
    cmp byte [msg], '9'       ; Compare it with '9'
    jbe repeat                 ; If it's <= '9', repeat the process

done:
    call exit                  ; Call the exit function

; Print function to write the message
print:
    mov eax, 4                 ; sys_write system call number (4)
    mov ebx, 1                 ; File descriptor for stdout (1)
    mov edx, 2                 ; Number of bytes to write (1 character + newline)
    int 0x80                   ; Interrupt to invoke the system call
    ret                        ; Return to the caller

; Exit function to exit the program
exit:
    mov eax, 1                 ; sys_exit system call number (1)
    xor ebx, ebx               ; Return code 0 (success)
    int 0x80                   ; Interrupt to invoke the system call
