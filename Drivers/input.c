#include "input.h"


uint8_t get_key()
{
    uint8_t scan_code = port_byte_in(KEYBOARD_DATA_IO_PORT);
    return map_port_to_ascii(scan_code);
}

uint8_t get_key_raw()
{
  	return port_byte_in(KEYBOARD_DATA_IO_PORT);
}

uint8_t map_port_to_ascii(uint8_t port)
{
    static uint8_t port_to_ascii[256] = {
        ' ', '1', '2', '3', '4', '5', '6', '7', '8', '9', '-', '=', ' ', ' ',
        ' ', 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', ' ', ' ',
        ' ', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/'
    };

    return port_to_ascii[port];
}

bool key_detected()
{
    uint8_t status = port_byte_in(KEYBOARD_CONTROL_IO_PORT);
    return (status & 0x01);
}