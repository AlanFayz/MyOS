#include "pit.h"
#include "../Drivers/low_level.h"
#include "../Drivers/screen.h"

#define PIT_BASE_FREQUENCY 1193182
#define PIC1_CMD 0x20
#define PIC1_DATA 0x21
#define PIC2_CMD 0xA0
#define PIC2_DATA 0xA1
#define PIC_EOI 0x20

typedef struct {
    uint32_t reload_value;
    uint32_t irq0_frequency;
    uint32_t irq0_ms;
    uint32_t irq0_fractions;
} pit_info_t;

typedef struct {
    uint32_t fractions;
    uint32_t ms;
} system_timer_t;

static pit_info_t pit_info;
static system_timer_t system_timer;

void pit_init(uint32_t frequency)
{
    if (frequency < 19) 
        frequency = 19; 

    if (frequency > PIT_BASE_FREQUENCY) 
        frequency = PIT_BASE_FREQUENCY;

    // Calculate the reload value
    uint16_t reload_value = (uint16_t)(PIT_BASE_FREQUENCY / frequency);

    port_byte_out(PIT_CONTROL_IO_PORT, 0x36);
    set_pit_count(reload_value);

}

uint16_t read_pit_count()
{
    uint16_t count = 0;

    disable_interrupts();

    port_byte_out(PIT_CONTROL_IO_PORT, 0);

    count  = port_byte_in(PIT_CONTROL_IO_PORT);
    count |= port_byte_in(PIT_CONTROL_IO_PORT) << 8;

    enable_interrupts();

    return count;
}

void set_pit_count(uint16_t count)
{
    uint8_t lower_bits = (uint8_t)(count & 0x00FF);
    uint8_t upper_bits = (uint8_t)((count >> 8) & 0x00FF);

    port_byte_out(PIT_CHANNEL_0_IO_PORT, lower_bits);
    port_byte_out(PIT_CHANNEL_0_IO_PORT, upper_bits);
}

void irq0_handler(interrupt_frame_t* ptr)
{
    system_timer.ms++;
    port_byte_out(END_OF_INTERRUPT, END_OF_INTERRUPT);
}
