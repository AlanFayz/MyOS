#include "mouse.h"

#include "Common/cpu.h"
#include "Common/Interrupts/irq.h"
#include "print.h"

#define PS2      0x64 
#define PS2_DATA 0x60

#define PS2_ENABLE 0xF4

#define PS2_ENABLE_PORT       0xA8
#define PS2_SET_SAMPLE_RATE   0xF3
#define PS2_GET_DEVICE_ID     0xF2
#define PS2_GET_CONFIG        0x20 
#define PS2_SET_CONFIG        0x60
#define PS2_ADDRESS_MOUSE     0xD4
#define PS2_DEFAULT_SETTINGS  0xF6

#define PS2_QEMU_DEVICE_ID 4

#define PS2_ACK 0xFA // acknowledgment from ps2

static int32_t mouse_x = 0;
static int32_t mouse_y = 0; 

void mouse_callback(const interrupt_frame_t* frame)
{
    static uint8_t packets[3];
    static uint8_t packet_index = 0;

    uint8_t data = port_byte_in(PS2_DATA);

    packets[packet_index++] = data;

    if(packet_index == 3)
    {
        int8_t dx = (int8_t)packets[1];
        int8_t dy = (int8_t)packets[2];

        mouse_x += (int32_t)dx;
        mouse_y += (int32_t)dy;

        packet_index = 0;
    }
}

static void mouse_wait()
{
    while(!(port_byte_in(PS2) & 1))
        pause();
} 

static void mouse_wait_write()
{
    while(port_byte_in(PS2) & 2)
        pause();
}

static void mouse_ack()
{
    mouse_wait();

    uint8_t ack = port_byte_in(PS2_DATA);
    
    if(ack != PS2_ACK)
    {
        panic();
    }

}

void init_mouse()
{    
    mouse_wait_write();
    port_byte_out(PS2, PS2_ENABLE_PORT);

    mouse_wait_write();
    port_byte_out(PS2, PS2_GET_CONFIG);
    mouse_wait();

    uint8_t config = (port_byte_in(PS2_DATA) | (1 << 1)); 
    mouse_wait_write();

    port_byte_out(PS2, PS2_DATA);
    
    mouse_wait();

    port_byte_out(PS2_DATA, config);

    port_byte_out(PS2, PS2_ADDRESS_MOUSE);
    port_byte_out(PS2_DATA, PS2_DEFAULT_SETTINGS);

    mouse_ack();

    port_byte_out(PS2, PS2_ADDRESS_MOUSE);
    port_byte_out(PS2_DATA, PS2_ENABLE);

    mouse_ack();

    irq_install_callback(12, mouse_callback);
}

int32_t mouse_get_x()
{
    return mouse_x;
}

int32_t mouse_get_y()
{
    return mouse_y;
}

// uhmmm, yeah I tried my best...
static uint8_t cursor_basic[8] = {
    0b00000001, 
    0b00000011, 
    0b00000111, 
    0b00001111, 
    0b00011011, 
    0b00110011, 
    0b01000011, 
    0b00000001  
};

void draw_cursor()
{
    gfx_color_t color = {0xFF, 0, 0xFF};

    uint16_t cursor_x = mouse_x;
    uint16_t cursor_y = gfx_get_height() - mouse_y;

    for(uint8_t y = 0; y < 8; y++)
    {
        for(uint8_t x = 0; x < 8; x++)
        {
            if(cursor_basic[y] & (1 << x))
            {
                gfx_draw_pixel(cursor_x + x, cursor_y + y, color);
            }
        }
    }
}