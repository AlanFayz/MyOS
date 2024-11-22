#pragma once

#include "Common/low_level.h"

#include <stdbool.h>

typedef struct {
    uint8_t scancode_ascii;
    uint8_t scancode;
    bool pressed;
    bool released;
} key_t;

key_t get_key();
bool key_detected();