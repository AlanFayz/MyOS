[bits 32]

%define VIDINFO 1 << 2

%define GRAPHICS_MODE 0

%define MULTIBOOT_MAGIC_NUMBER 0x1BADB002
%define MULTIBOOT_FLAGS (VIDINFO)
%define MULTIBOOT_CHECKSUM -(MULTIBOOT_MAGIC_NUMBER + MULTIBOOT_FLAGS) 

%define WIDTH  1024 
%define HEIGHT 768 
%define DEPTH  32

section .multiboot 
    align 4
    dd MULTIBOOT_MAGIC_NUMBER
    dd MULTIBOOT_FLAGS
    dd MULTIBOOT_CHECKSUM
    dd 0, 0, 0, 0, 0
    dd GRAPHICS_MODE
    dd WIDTH, HEIGHT, DEPTH

section .bss 
    align 16
    stack_bottom:
        resb 16384
    stack_top:

section .text 
    global start 

    extern kernel_start
    extern init_kernel 
    extern init_gdt
    extern init_idt

    start:
        cli 

        mov esp, stack_top 

        push 0
        popf

        push ebx ; multiboot header pointer
        push eax ; multiboot magic number

        call init_gdt
        call init_idt
        call init_kernel

        popf 
        popf

        call kernel_start 
        
    panic:
        cli
        hlt
        jmp panic

    

