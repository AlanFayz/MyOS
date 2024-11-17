#include "screen.h"
#include "input.h"
#include "Interrupts/idt.h"

#include "memory.h"

void kernel_init()
{
    screen_clear(0);
    //idt_init();
}

void main()
{
    kernel_init();

    while(true)
    {
        screen_put_char('a', 0);
        halt();
    }
}


