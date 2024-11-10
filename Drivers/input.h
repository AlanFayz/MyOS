#pragma once

#include "low_level.h"
#include "../Kernel/bool.h"

uint8_t get_key();
uint8_t get_key_raw();
uint8_t map_port_to_ascii(uint8_t port);
bool key_detected();