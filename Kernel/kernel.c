#include "screen.h"
#include "input.h"
#include "Interrupts/idt.h"

#include "memory.h"

void kernel_init()
{
    screen_clear(0);
    idt_init();

    screen_print_string("Kernel Has Initialized\n", 0);

    int val = 10 / 0;
}

void main()
{
    kernel_init();

    while(true)
    {
        halt();
    }
}


