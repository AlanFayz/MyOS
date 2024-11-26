#include "cpu.h"

uint8_t port_byte_in(uint16_t port)
{
    uint8_t result;
    __asm__("in %%dx, %%al" : "=a" (result) : "d" (port));
    return result;
}

uint16_t port_word_in(uint16_t port)
{
    uint16_t result;
    __asm__("in %%dx, %%ax" : "=a" (result) : "d" (port));
    return result;
}

void port_byte_out(uint16_t port, uint8_t data)
{
    __asm__("out %%al, %%dx" : : "a" (data), "d" (port));
}

void port_word_out(uint16_t port, uint16_t data)
{
    __asm__("out %%ax, %%dx" : : "a" (data), "d" (port));
}

void panic()
{
    //maybe print something?
    for(;;)
    {
        hlt();
    }
}

void sti()
{
    __asm__("sti");
}

void cli()
{
    __asm__("cli");
}

void hlt()
{
	__asm__("hlt");
}