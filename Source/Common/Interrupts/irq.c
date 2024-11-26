#include "irq.h"

#include "Common/low_level.h"
#include "Kernel/System/print.h"

#define PIC1      0x20
#define PIC1_DATA 0x21

#define PIC2      0xA0
#define PIC2_DATA 0xA1

#define EOI 0x20

irq_callback_t irq_callbacks[16] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0
};


void irq_handler(const interrupt_frame_t* frame)
{
    irq_callback_t handler = irq_callbacks[frame->int_number - 32];

    if(handler)
    {
        handler(frame);
    }

    if(frame->int_number >= 40)
    {
        port_byte_out(PIC2, EOI);
    }

    port_byte_out(PIC1, EOI);
}

void irq_install_callback(int8_t index, irq_callback_t callback)
{
    irq_callbacks[index] = callback;
}

void irq_remove_callback(int8_t index)
{
    irq_callbacks[index] = 0;
}
