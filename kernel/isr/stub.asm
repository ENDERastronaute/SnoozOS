
[bits 32]

[extern interrupt_dispatch]

%macro GENERATE_HANDLER 1 ; Vladilena Milizé on top
    align 8

    global vector_%1_handler
    
    vector_%1_handler:
        push 0
        push %1 
        jmp interrupt_stub

%endmacro

%assign i 0

%rep 256
    GENERATE_HANDLER i
    %assign i i + 1
%endrep

interrupt_stub:
    call interrupt_dispatch

    add esp, 8

    iret
