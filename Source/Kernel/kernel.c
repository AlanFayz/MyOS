#include <stdint.h>
#include <stdbool.h>

#include "Common/low_level.h"

#include "System/timer.h"
#include "System/print.h"

#include "gfx.h"

void gfx_test()
{
    gfx_color_t test_color;
    test_color.b = 0xFF;

    uint32_t height = gfx_get_height();
    uint32_t width  = gfx_get_width();


    for(uint32_t y = 0; y < height; y++)
    {
        for(uint32_t x = 0; x < width; x++)
        {
            float c = (float)x / (float)width;
            int8_t color = (int8_t)(c * 255.0);

            test_color.g = 255 - color;   
            test_color.r = color;

            gfx_draw_pixel(x, y, test_color);
        }
    }
}

void kernel_start() 
{
    gfx_character_t character;
    character.character = 'A';
    character.width  = 100;
    character.height = 100;
    character.x = 250;
    character.y = 250;

    gfx_color_t color;
    color.r = 10;
    color.g = 50;
    color.b = 255;

    gfx_draw_character(character, color);

    print(20, 20, color, "hello");
    print_float(20, 50, color, 4, 50.1);

    while(1)
    {
        print_int(500, 10, color, system_timer_get_ticks());
    }
}
