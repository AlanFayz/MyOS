#pragma once

#include "low_level.h"

typedef uint8_t vga_color_t;

typedef struct {
    uint32_t row;
    uint32_t column;
} cursor_t;

typedef struct {
  uint8_t*    framebuffer;
  uint16_t    rows;
  uint16_t    columns;
  cursor_t    cursor;
  vga_color_t white_on_black;
} screen_t;

void     cursor_set(uint32_t row, uint32_t column);
void     cursor_increment();
uint32_t cursor_get_index();

cursor_t screen_get_cursor();
void     screen_clear(vga_color_t color);
void     screen_put_char(int8_t c, vga_color_t color);
void     screen_put_int(int32_t value, vga_color_t color);
void     screen_put_hex(uint32_t value, vga_color_t color);
void     screen_print_string(const char* str, vga_color_t color);
void     screen_shift_down();
void     screen_shift_up();
