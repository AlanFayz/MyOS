#include "../Drivers/screen.h"
#include "../Drivers/input.h"

#include "pit.h"
#include "memory.h"

void kernel_init()
{
    screen_clear(0);
    //TODO: need to set up interrupt discriptor table
    //pit_init(100);

    //enable_interrupts();
}

void main()
{
    kernel_init();

    while(true)
    {
    }
}


