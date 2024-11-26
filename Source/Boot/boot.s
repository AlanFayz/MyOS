[bits 32]

%define VIDINFO 1 << 2

%define GRAPHICS_MODE 0

; magic number lets multiboot know this is a multiboot header
%define MULTIBOOT_MAGIC_NUMBER 0x1BADB002 
%define MULTIBOOT_FLAGS (VIDINFO)
%define MULTIBOOT_CHECKSUM -(MULTIBOOT_MAGIC_NUMBER + MULTIBOOT_FLAGS) 

; we want to request this specific vesa mode.
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
        cli ; clear any previous interrupts

        mov esp, stack_top 
    
        ; resets eflags register
        push 0
        popf

        push ebx ; multiboot information struct pointer
        push eax ; multiboot magic number

        call init_gdt     ; global descriptor table
        call init_idt     ; interrupt descriptor table
        call init_kernel  

        add esp, 8

        call kernel_start 
        
    panic:
        cli
        hlt
        jmp panic

    

