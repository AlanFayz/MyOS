#pragma once 

#include "multiboot.h"

#include <stdint.h>

typedef struct {
    uint8_t b, g, r, _reserved;
} __attribute__((packed)) gfx_color_t;

typedef struct {
    int16_t x, y; //center
    uint16_t width, height;
} gfx_rect_2d_t;

typedef struct {
    int16_t x, y; //center
    int16_t radius;
} gfx_circle_t;

typedef struct {
    int16_t x, y;
    char character
} gfx_character_t;

typedef struct {
    uint32_t width; 
    uint32_t height;

    uint8_t  red_shift;
    uint8_t  blue_shift;
    uint8_t  green_shift;

    uint32_t pitch; //number of bytes per row

    gfx_color_t* framebuffer_address;
} gfx_driver_info_t;

void init_gfx(multiboot_info_t* mbi);

uint32_t gfx_get_width();
uint32_t gfx_get_height();

void gfx_draw_pixel(int16_t x, int16_t y, gfx_color_t color);
void gfx_draw_rect(gfx_rect_2d_t rect,    gfx_color_t color);
void gfx_draw_circle(gfx_circle_t circle, gfx_color_t color);
void gfx_draw_character(gfx_character_t character, gfx_color_t color);

uint32_t gfx_color_to_rgb(gfx_color_t color);