#pragma once 

#include <stdint.h>

typedef struct {
    uint32_t ticks;
} system_timer_t;

void init_system_timer();

uint32_t system_timer_get_ticks();