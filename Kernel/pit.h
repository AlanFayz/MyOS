#pragma once

#include <stdint.h>

//programmable interval timer

void pit_init(uint32_t frequency);
uint16_t read_pit_count();
void set_pit_count(uint16_t count);

void irq0_handler();