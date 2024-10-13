[bits 16]

switch_to_protected:
    cli ; disable interrupts

    lgdt [gdt_descriptor] ; load gdt

    ; switch to protected
    mov eax, cr0
    or eax, 0x1
    mov cr0, eax

    jmp CODE_SEG:init_pm ; far jump (flush the pipeline)



[bits 32]
; initialize registers and the stack
init_pm:
    mov ax, DATA_SEG ; point segment registers to data selector
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov ebp, 0x90000 ; stack pos to top of free space
    mov esp, ebp

    jmp protected ; next