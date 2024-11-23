#include "timer.h"

#include "Common/Interrupts/irq.h"
#include "Common/low_level.h"
#include "print.h"

#define PIT_FREQUENCY 1193182

static volatile uint32_t system_ticks;

void timer_callback(const interrupt_frame_t* frame)
{
    system_ticks += 1; 
}

void init_system_timer()
{
    const uint32_t desired_frequency = 100; //(hz)
    const uint32_t divisor = PIT_FREQUENCY / desired_frequency;

    system_ticks = 0;
    irq_install_callback(0, &timer_callback);

    port_byte_out(PIT_CONTROL_IO_PORT, 0x36);
    port_byte_out(PIT_CHANNEL_0_IO_PORT, divisor & 0xFF); //low bytes
    port_byte_out(PIT_CHANNEL_0_IO_PORT, (divisor >> 8) & 0xFF); //high bytes
}

uint32_t system_timer_get_ticks()
{
    return system_ticks;
}
