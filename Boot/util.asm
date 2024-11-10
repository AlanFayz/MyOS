print:
    pusha
    mov ah, 0x0e

loop_start:
    mov al, [si]
    inc si
    int 0x10

    mov al, [si]
    cmp al, 0
    jne loop_start

    popa
    ret


print_nl:
    mov al, 0x0A
    mov ah, 0x0e
    int 0x10
    mov al, 0x0d
    int 0x10
    ret


; assumes hex string is put in dx
print_hex:
    pusha

    mov cl, 16

loop_start2:
    sub cl, 4

    mov ax, dx
    shr ax, cl

    and al, 0x0F

    cmp al, 10
    jge letter
    jmp number

letter:
    add al, 55
    jmp merge

number:
    add al, 48
    jmp merge

merge:
    mov ah, 0x0e
    int 0x10
    cmp cl, 0
    jne loop_start2

    popa
    ret

halt:
    jmp $