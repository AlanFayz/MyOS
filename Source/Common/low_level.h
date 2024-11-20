#pragma once

#include <stdint.h>

#define SCREEN_CONTROL_IO_PORT   ((uint16_t)0x3D4)
#define SCREEN_DATA_IO_PORT      ((uint16_t)0x3D5)
#define KEYBOARD_CONTROL_IO_PORT ((uint16_t)0x64)
#define KEYBOARD_DATA_IO_PORT    ((uint16_t)0x60)
#define PIT_CONTROL_IO_PORT      ((uint16_t)0x43)
#define PIT_CHANNEL_0_IO_PORT    ((uint16_t)0x40)
#define END_OF_INTERRUPT         ((uint16_t)0x20)


uint8_t  port_byte_in(uint16_t port);
uint16_t port_word_in(uint16_t port);
void port_byte_out(uint16_t port,  uint8_t data);
void port_word_out(uint16_t port, uint16_t data);

void halt();
void pause();
void enable_interrupts();
void disable_interrupts();