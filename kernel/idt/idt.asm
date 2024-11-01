[bits 32]

global idt_flush

idt_flush:
    mov eax, [esp+4] ; get idt from stack
    lidt [eax]
    sti
    ret

%macro ISR_NOERR 1
    global isr%1
    isr%1:
        cli
        push long 0
        push long %1 
        JMP isr_stub
%endmacro

%macro ISR_ERR 1
    global isr%1 
    isr%1:
        cli
        push long %1 
        jmp isr_stub

%endmacro

%macro IRQ 2
    global irq%1
    irq%1:
        cli
        push long 0
        push long %2
        jmp irq_stub

%endmacro

%assign i 0

%rep 8
    ISR_NOERR i 
    %assign i i + 1
%endrep

ISR_ERR 8
ISR_NOERR 9

%assign i 10

%rep 5
    ISR_ERR i 
    %assign i i + 1
%endrep

%rep 17
    ISR_NOERR i 
    %assign i i + 1
%endrep

ISR_NOERR 128
ISR_ERR 177

%assign i 0
%assign j 32

%rep 16
    IRQ i, j
    %assign i i + 1
    %assign j j + 1
%endrep

extern isr_handler

isr_stub:
    pusha
    mov eax, ds
    push eax
    mov eax, cr2
    push eax

    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    push esp
    call isr_handler

    add esp, 8
    pop ebx
    mov ds, bx
    mov es, bx
    mov fs, bx
    mov gs, bx
    
    popa

    add esp, 8

    sti

    iret

extern irq_handler

irq_stub:
    pusha
    mov eax, ds
    push eax
    mov eax, cr2
    push eax

    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    push esp
    call irq_handler

    add esp, 8
    pop ebx
    mov ds, bx
    mov es, bx
    mov fs, bx
    mov gs, bx
    
    popa

    add esp, 8

    sti

    iret 
