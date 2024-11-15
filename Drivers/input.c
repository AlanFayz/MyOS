#include "input.h"

#define KEY_RELEASED_THRESOLD 129

//for now only with qwerty american layout and doesn't deal with shifts
static uint8_t map_port_to_ascii(uint8_t port)
{
    static uint8_t port_to_ascii[256] = {
        ' ', ' ', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=',
        ' ', ' ', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']',
        '\\', ' ', 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', ' ',
        ' ', ' ', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/',
    };

    return port_to_ascii[port];
}

key_t get_key()
{
    key_t key;
    key.scancode = port_byte_in(KEYBOARD_DATA_IO_PORT);
    key.pressed  = key.scancode < KEY_RELEASED_THRESOLD ? true : false;
    key.released = !key.pressed;
    key.scancode_ascii = key.pressed ? map_port_to_ascii(key.scancode) : map_port_to_ascii(key.scancode - KEY_RELEASED_THRESOLD + 1);

    return key;
}



bool key_detected()
{
    uint8_t status = port_byte_in(KEYBOARD_CONTROL_IO_PORT);
    return (status & 0x01);
}