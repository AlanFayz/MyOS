#include "isr.h"

#include "Kernel/System/print.h"

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
    if(frame->int_number < 32)
    {
        int16_t center_x = gfx_get_width() / 2;
        int16_t center_y = gfx_get_height() / 2;

        gfx_color_t color = {0xFF, 0XFF, 0xFF};

        print(center_x, center_y, color, exception_messages[frame->int_number]);
        for(;;)
        {
            halt();
        }
    }
}