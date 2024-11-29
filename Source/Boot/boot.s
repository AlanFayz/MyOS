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

%define CODE_SEGMENT 0x08
%define DATA_SEGMENT 0x10

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
        resb 1048576 
    stack_top:

    ; allocate memory for backbuffer as we don't have malloc, heap section should go here in the future
    back_buffer_bottom: 
        resb WIDTH * HEIGHT * DEPTH
    back_buffer_top:

section .text 
    global start 
    global gdt_flush 
    global tss_flush
    global idt_flush

    extern kernel_start
    extern init_kernel 
    extern init_gdt
    extern init_idt

    ; entry after multiboot finishes bootloading
    start:
        cli ; clear any previous interrupts

        mov esp, stack_top 
    
        ; resets eflags register
        push 0
        popf

        push ebx ; multiboot information struct pointer
        push eax ; multiboot magic number
        push back_buffer_bottom

        call init_gdt     ; global descriptor table
        call init_idt     ; interrupt descriptor table
        call init_kernel  

        add esp, 12

        call kernel_start 
        
    fall:
        cli
        hlt
        jmp fall

    ; loads the global descriptor table and adjusts registers.
    gdt_flush:
        mov eax, [esp + 4]
        lgdt [eax]

        mov eax, DATA_SEGMENT
        mov ds, ax 
        mov es, ax 
        mov fs, ax 
        mov gs, ax 
        mov ss, ax

        jmp CODE_SEGMENT:long_jump

    long_jump:
        ret  

    ; loads task state segment 
    tss_flush:
        mov ax, 0x2B
        ltr ax 
        ret

    ; loads interrupt descriptor table and enables interrupts
    idt_flush:
        mov eax, [esp + 4]
        lidt [eax]
        sti 
        ret 

    

