#pragma once 

#include "Kernel/gfx.h"

int8_t print_int(int16_t x,  int16_t y, gfx_color_t color, int32_t value);
void print_bin(int16_t x,  int16_t y, gfx_color_t color, uint32_t value);
void print_hex(int16_t x,  int16_t y, gfx_color_t color, uint32_t value);
void print_char(int16_t x, int16_t y, gfx_color_t color, char value);
void print_float(int16_t x, int16_t y, gfx_color_t color, int8_t dp, double value);
void print(int16_t x, int16_t y, gfx_color_t color, const char* value);