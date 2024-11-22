#include "isr.h"

#include "Kernel/screen.h"

const char* exception_messages[] = {
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",
    "Coprocessor Fault",
    "Alignment Check",
    "Machine Check",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};

void isr_handler(const interrupt_frame_t* frame)
{ 
    if(frame->int_number == 13)
    {
        halt();
        return;
    }

    if(frame->int_number < 31)
    {
        screen_print_string(exception_messages[frame->int_number], 0);
        screen_put_char('\n', 0);
        screen_put_int(frame->error_code, 0);
        screen_put_char('\n', 0);
        for(;;);
    }
}
