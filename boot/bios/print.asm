[bits 16]

print_char:
    pusha
    mov ah, 0xE

print_char_loop:
    mov al, [bx]
    cmp al, 0
    je end_print
    int 0x10
    inc bx
    jmp print_char_loop

end_print:
    popa
    ret