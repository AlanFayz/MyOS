#include "timer.h"

#include "Common/Interrupts/irq.h"
#include "Common/cpu.h"
#include "print.h"

#define PIT_FREQUENCY 1193182
#define PIT_CONTROL 0x43
#define PIT_CHANNEL 0x40
#define PIT_FLAGS 0x36

static volatile uint32_t system_ticks;

void timer_callback(const interrupt_frame_t* frame)
{
    system_ticks++;
}

void init_system_timer()
{
    const uint32_t desired_frequency = 100; //(hz)
    const uint32_t divisor = PIT_FREQUENCY / desired_frequency;

    system_ticks = 0;
    irq_install_callback(0, timer_callback);

    port_byte_out(PIT_CONTROL, PIT_FLAGS);
    port_byte_out(PIT_CHANNEL, divisor & 0xFF); //low bytes
    port_byte_out(PIT_CHANNEL, (divisor >> 8) & 0xFF); //high bytes
}

uint32_t system_timer_get_ticks()
{
    return system_ticks;
}
