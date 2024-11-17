#include "isr.h"
#include "screen.h"

char *exception_messages[] = {
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",
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
    if(frame->int_number < 31)
    {
        screen_print_string("                           ", 0);
        screen_print_string(" exception ", 0);
        screen_put_bin(frame->error_code, 0);
        screen_print_string(" interrupt number:  ", 0);
        screen_put_int(frame->int_number, 0);
        screen_print_string("  data segment: ", 0);
        screen_put_int(frame->ds, 0);
        halt();
    }
}
