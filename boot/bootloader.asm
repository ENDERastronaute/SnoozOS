
; real-mode
[org 0x7c00]
    KERNEL_OFFSET equ 0x1000

    mov [BOOT_DRIVE], dl ; bios stores boot drive

    mov bp, 0x9000 ; set stack
    mov sp, bp

    mov bx, real_msg ; print_char(real)
    call print_char

    call load_kernel

    call switch_to_protected

    jmp $ ; end loop
; -- real-mode

; includes
%include "pm/gdt.asm"
%include "pm/protected.asm"
%include "bios/print.asm"
%include "disk/disk_load.asm"
; -- includes

[bits 16]

load_kernel:
    mov bx, KERNEL_OFFSET ; load first 15 sectors (excluding boot) from boot disk to address KERNEL_OFFSET
    mov dh, 16
    mov dl, [BOOT_DRIVE]
    call disk_load

    ret

[bits 32]

; protected-mode
protected:
    call KERNEL_OFFSET

    jmp $

; -- protected-mode

; data
real_msg: db 'Starting bootloader', 0
BOOT_DRIVE: db 0
; -- data

; make bootable

times 510-($-$$) db 0
dw 0xAA55
