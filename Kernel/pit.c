#include "pit.h"
#include "../Drivers/low_level.h"

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
    uint32_t reload_value;
    uint32_t actual_frequency;
    uint32_t irq_time_ms;
    uint32_t irq_time_fraction;

    if (frequency <= 18) 
    {
        reload_value = 0x10000;  // Slowest possible frequency (65536)
    } 
    else if (frequency >= 1193181) 
    {
        reload_value = 1;  // Fastest possible frequency (1)
    } 
    else 
    {
        reload_value = 3579545 / frequency;
        uint32_t remainder = 3579545 % frequency;

        if (remainder > (3579545 / 2)) 
        {
            reload_value++;
        }

        reload_value = (reload_value * 256) / 3;
        remainder = reload_value % 3;
        
        if (remainder > 1) 
        {
            reload_value++;
        }
    }

    pit_info.reload_value = (uint16_t)reload_value;

    actual_frequency = 3579545 / reload_value;
    uint32_t remainder = 3579545 % reload_value;
    
    if (remainder > (3579545 / 2)) 
    {
        actual_frequency++;
    }

    actual_frequency = (actual_frequency * 256) / 3;
    remainder = actual_frequency % 3;
    
    if (remainder > 1) 
    {
        actual_frequency++;
    }

    pit_info.irq0_frequency = actual_frequency;

    irq_time_ms = (reload_value * 3000 * (1 << 42)) / 3579545;
    irq_time_fraction = (reload_value * 3000 * (1 << 42)) / 3579545;

    pit_info.irq0_ms = irq_time_ms >> 10;  
    pit_info.irq0_fractions = irq_time_fraction >> 10;  

    disable_interrupts();

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

void irq0_handler()
{
    system_timer.fractions += pit_info.irq0_fractions;
    system_timer.ms += pit_info.irq0_ms;

    port_byte_out(END_OF_INTERRUPT, END_OF_INTERRUPT);
}
