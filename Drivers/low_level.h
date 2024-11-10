#pragma once

#include <stdint.h>


#define SCREEN_CONTROL_IO_PORT ((uint16_t)0x3D4)
#define SCREEN_DATA_IO_PORT    ((uint16_t)0x3D5)

uint8_t  port_byte_in(uint16_t port);
uint16_t port_word_in(uint16_t port);
void port_byte_out(uint16_t port,  uint8_t data);
void port_word_out(uint16_t port, uint16_t data);
