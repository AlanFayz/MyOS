#include "gfx.h"
#include "font.h"

#define BLUE_COLOR_SHIFT   0
#define GREEN_COLOR_SHIFT  8
#define RED_COLOR_SHIFT    16

static gfx_driver_info_t gfx_driver;

void init_gfx(multiboot_info_t* mbi)
{
    gfx_driver.framebuffer_address = (uint32_t*)mbi->framebuffer_addr;
    gfx_driver.width       = mbi->framebuffer_width;
    gfx_driver.height      = mbi->framebuffer_height;
    gfx_driver.blue_shift  = mbi->framebuffer_blue_field_position;
    gfx_driver.red_shift   = mbi->framebuffer_red_field_position;
    gfx_driver.green_shift = mbi->framebuffer_green_field_position;
    gfx_driver.pitch       = mbi->framebuffer_pitch;
}

uint32_t gfx_get_width()
{
    return gfx_driver.width;
}

uint32_t gfx_get_height()
{
    return gfx_driver.height;
}

void gfx_draw_pixel(int16_t x, int16_t y, gfx_color_t color)
{
    if(x >= gfx_driver.width || y >= gfx_driver.height || x < 0 || y < 0) 
    {
        return;
    }

    uint32_t* pixel = gfx_driver.framebuffer_address + y * gfx_driver.pitch / sizeof(uint32_t) + x;
    *pixel = gfx_color_to_rgb(color);
}

void gfx_draw_rect(gfx_rect_2d_t rect, gfx_color_t color)
{
    int16_t min_x = rect.x - rect.width / 2;
    int16_t min_y = rect.y - rect.height / 2;

    int16_t max_x = rect.x + rect.width / 2;
    int16_t max_y = rect.y + rect.height / 2;


    for(int16_t y = min_y; y < max_y; y++)
    {
        for(int16_t x = min_x; x < max_x; x++)
        {
            gfx_draw_pixel(x, y, color);
        }
    }
}

void gfx_draw_circle(gfx_circle_t circle, gfx_color_t color)
{
    int16_t min_x = circle.x - circle.radius;
    int16_t min_y = circle.y - circle.radius;

    int16_t max_x = circle.x + circle.radius;
    int16_t max_y = circle.y + circle.radius;

    int16_t r_squared = circle.radius * circle.radius;

    for(int16_t y = min_y; y < max_y; y++)
    {
        for(int16_t x = min_x; x < max_x; x++)
        {
            int16_t x_squared = (x - circle.x) * (x - circle.x);
            int16_t y_squared = (y - circle.y) * (y - circle.y);

            if(x_squared + y_squared <= r_squared)
                gfx_draw_pixel(x, y, color);
        }
    }
}

void gfx_draw_character(gfx_character_t character, gfx_color_t color)
{
    char* bitmap = font8x8_basic[character.character];


    for (int16_t y = 0; y < character.height; y++) 
    {
        float normalised_y = (float)y / (float)character.height;
        int8_t y_coord = (int8_t)(normalised_y * 8.0f);

        for (int16_t x = 0; x < character.width; x++) 
        {
            float normalised_x = (float)x / (float)character.width;
            int8_t x_coord = (int8_t)(normalised_x * 8.0f);

            if (bitmap[y_coord] & (1 << x_coord))
            {
                //swapped x and y coord to rotate by 90 degrees
                gfx_draw_pixel(character.x + x, character.y + y, color);
            }
        }
    }
}

uint32_t gfx_color_to_rgb(gfx_color_t color)
{
    return (color.b << gfx_driver.blue_shift) | (color.g << gfx_driver.green_shift) | (color.r << gfx_driver.red_shift);
}