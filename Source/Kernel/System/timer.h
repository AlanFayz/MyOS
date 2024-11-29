#pragma once 

#include <stdint.h>

void init_system_timer();

uint64_t system_timer_get_ticks();
double   system_timer_get_ticks_seconds();

void sleep(uint32_t time_s);