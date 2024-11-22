#include "irq.h"

#include "Common/low_level.h"

void* irq_callbacks[16] = {
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
        port_byte_out(0xA0, 0x20);
    }

    port_byte_out(0x20, 0x20);
}

void irq_install_callback(int8_t index, irq_callback_t callback)
{
    if(index > 15) // ??
    {
        for(;;);
    }

    irq_callbacks[index] = callback;
}

void irq_remove_callback(int8_t index)
{
    if(index > 15) // ??
    {
        for(;;);
    }


    irq_callbacks[index] = 0;
}
