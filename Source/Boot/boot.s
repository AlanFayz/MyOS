[bits 32]

%define MULTIBOOT_MAGIC_NUMBER 0x1BADB002
%define MULTIBOOT_FLAGS 0
%define MULTIBOOT_CHECKSUM -(MULTIBOOT_MAGIC_NUMBER + MULTIBOOT_FLAGS)

section .multiboot 
    align 4
    dd MULTIBOOT_MAGIC_NUMBER
    dd MULTIBOOT_FLAGS
    dd MULTIBOOT_CHECKSUM


section .bss 
    align 16
    stack_bottom:
        resb 16384
    stack_top:

section .text 
    global start 

    extern kernel_start 
    extern init_gdt
    extern init_idt

    start:
        mov esp, stack_top 

        call init_gdt
        call init_idt

        call kernel_start 

    kernel_halt:
        cli
        hlt
        jmp kernel_halt

    

