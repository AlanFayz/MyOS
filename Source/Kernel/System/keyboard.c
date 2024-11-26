#include "keyboard.h"

#include "Common/Interrupts/irq.h"
#include "print.h"

#include "Kernel/gfx.h"

#define KEYBOARD_ACK         0xFA
#define KEYBOARD_RESEND      0xFE
#define KEYBOARD_CMD_SCANCODE 0xF0
#define KEYBOARD_DATA        0x60
#define KEYBOARD_CONTROL     0x64

#define KEY_RELEASE_BIT 0x80 
#define KEY_MASK 0x7F

#define MAX_KEYS 128

static key_status_t keys[MAX_KEYS] = {KEY_STATUS_RELEASED}; 

static void set_key_status(uint8_t key, key_status_t status)
{
    if (key < MAX_KEYS) 
    {
        keys[key] = status;
    }
}

key_status_t get_key_status(key_t key)
{
    if(key < MAX_KEYS)
    {
        return keys[key];
    }

    return KEY_STATUS_ERROR;
}

void keyboard_callback(const interrupt_frame_t* frame)
{
    uint8_t key_status = port_byte_in(KEYBOARD_DATA);

    if(key_status & KEY_RELEASE_BIT)
    {
        uint8_t key = key_status & KEY_MASK;
        set_key_status(key, KEY_STATUS_RELEASED);
    }
    else 
    {
        if(keys[key_status] == KEY_STATUS_RELEASED)
            set_key_status(key_status, KEY_STATUS_PRESSED);
        else 
            set_key_status(key_status, KEY_STATUS_HELD);
    }
}

void init_keyboard()
{
    irq_install_callback(1, keyboard_callback);
}