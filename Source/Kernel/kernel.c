#include <stdint.h>
#include <stdbool.h>

#include "System/timer.h"
#include "System/print.h"
#include "System/keyboard.h"

#include "Common/cpu.h"

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
    gfx_color_t color = {0xFF, 0xAA, 0};
    
    int x = 0;
    int y = 0;

    for(;;)
    {
        hlt();
    
        if(get_key_status(KEY_U) == KEY_STATUS_PRESSED)
        {
            print(300, 200, color, "0 key pressed");
        }
    }
}


