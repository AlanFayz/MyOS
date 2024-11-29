#include "timer.h"

#include "Common/Interrupts/irq.h"
#include "Common/cpu.h"
#include "print.h"

#define PIT_FREQUENCY 1193182
#define PIT_CONTROL 0x43
#define PIT_CHANNEL 0x40
#define PIT_FLAGS   0x36

#define PIT_CALL_FREQUENCY 100

static volatile uint64_t system_ticks;

void timer_callback(const interrupt_frame_t* frame)
{
    system_ticks++;
}

void init_system_timer()
{
    const uint32_t divisor = PIT_FREQUENCY / PIT_CALL_FREQUENCY;

    system_ticks = 0;

    irq_install_callback(0, timer_callback);

    port_byte_out(PIT_CONTROL, PIT_FLAGS);
    port_byte_out(PIT_CHANNEL, divisor & 0xFF); //low bytes
    port_byte_out(PIT_CHANNEL, (divisor >> 8) & 0xFF); //high bytes
}

uint64_t system_timer_get_ticks()
{
    return system_ticks;
}

double system_timer_get_ticks_seconds()
{
    return system_ticks * (1.0 / PIT_CALL_FREQUENCY);
}

void sleep(uint32_t time_s)
{
    uint64_t target_ticks = system_ticks + PIT_CALL_FREQUENCY * (uint64_t)time_s;  

    while (system_ticks < target_ticks)
    {
        hlt();  
    }
}

