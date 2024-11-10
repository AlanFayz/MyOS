[org 0x7c00]
KERNEL_OFFSET equ 0x1000

start:
    mov [BOOT_DRIVE], dl ; bios stores loaded boot drive in dl
    mov bp, 0x9000 ; set up the stack
    mov sp, bp

    mov bx, MSG_REAL_MODE
    call print
    call print_nl

    call load_kernel
    call switch_to_pm
    jmp $

%include "Boot/util.asm"
%include "Boot/disk.asm"
%include "Boot/gdt.asm"
%include "Boot/debug_print.asm"
%include "Boot/switch_pm.asm"

[bits 16]
load_kernel:
    mov bx, MSG_LOAD_KERNEL
    call print
    call print_nl

    mov bx, KERNEL_OFFSET ; load the first 15 sectors into kernel_offset
    mov dh, 15
    mov dl, [BOOT_DRIVE]
    call disk_load
    ret

[bits 32]
BEGIN_PM:
    mov ebx, MSG_PROT_MODE
    call print_string_pm
    call KERNEL_OFFSET ; call main in kernel.c


BOOT_DRIVE db 0
MSG_REAL_MODE db "Started in 16-bit Real Mode", 0
MSG_PROT_MODE db "Landed in 32-bit Protected Mode", 0
MSG_LOAD_KERNEL db "Loading kernel into memory", 0

times 510 - ($-$$) db 0
dw 0xaa55
