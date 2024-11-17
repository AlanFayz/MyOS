#include "isr.h"
#include "screen.h"

void isr_handler(const interrupt_frame_t* frame)
{
    if(frame->int_number)
    {
        screen_print_string(" exception ", 0);
        screen_put_int((int32_t)frame->error_code, 0);
        halt();
    }
}