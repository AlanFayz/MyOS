[bits 16]
switch_to_pm:
    cli ; clear interupts
    lgdt [gdt_descriptor]
    mov eax, cr0
    or eax, 0x1
    mov cr0, eax ; set the bit in cr0 to switch to 32 bit mode
    jmp CODE_SEG:init_pm

[bits 32]
init_pm:
    mov ax, DATA_SEG ; data segment in registers need to be updated
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov ebp, 0x90000 ; set up te stack
    mov esp, ebp

    call BEGIN_PM ; call global function
