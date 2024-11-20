
#include "screen.h"

void kernel_start()
{

    while(1)
    {
        screen_print_string("Welcome!", 0);
        for(uint32_t i = 0; i < 10000000; i++);
    }
}