[bits 32]

%macro ISR_NO_ERROR_CODE 1
    global isr%1
    isr%1:
        cli
        push dword 0         ; Push dummy error code.
        push dword %1        ; Push interrupt number.
        jmp isr_common
%endmacro

%macro ISR_ERROR_CODE 1
    global isr%1
    isr%1:
        cli
        push dword %1        ; Push interrupt number again.
        jmp isr_common
%endmacro

; Define interrupt handlers
ISR_NO_ERROR_CODE 0
ISR_NO_ERROR_CODE 1
ISR_NO_ERROR_CODE 2
ISR_NO_ERROR_CODE 3
ISR_NO_ERROR_CODE 4
ISR_NO_ERROR_CODE 5
ISR_NO_ERROR_CODE 6
ISR_NO_ERROR_CODE 7

ISR_ERROR_CODE 8

ISR_NO_ERROR_CODE 9

ISR_ERROR_CODE 10
ISR_ERROR_CODE 11
ISR_ERROR_CODE 12
ISR_ERROR_CODE 13
ISR_ERROR_CODE 14

ISR_NO_ERROR_CODE 15
ISR_NO_ERROR_CODE 16
ISR_NO_ERROR_CODE 17
ISR_NO_ERROR_CODE 18
ISR_NO_ERROR_CODE 19
ISR_NO_ERROR_CODE 20
ISR_NO_ERROR_CODE 21
ISR_NO_ERROR_CODE 22
ISR_NO_ERROR_CODE 23
ISR_NO_ERROR_CODE 24
ISR_NO_ERROR_CODE 25
ISR_NO_ERROR_CODE 26
ISR_NO_ERROR_CODE 27
ISR_NO_ERROR_CODE 28
ISR_NO_ERROR_CODE 29
ISR_NO_ERROR_CODE 30
ISR_NO_ERROR_CODE 31
ISR_NO_ERROR_CODE 128
ISR_NO_ERROR_CODE 177

extern isr_handler
isr_common:
    push esp
    call isr_handler
    add esp, 8
    sti
    iret
