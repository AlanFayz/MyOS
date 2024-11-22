#include <stdint.h>
#include <stdbool.h>

#include "Common/low_level.h"
#include "gfx.h"
#include "multiboot.h"

void init_kernel(uint32_t magic, uint32_t address)
{
    multiboot_info_t* mbi;

    if(magic != MULTIBOOT_BOOTLOADER_MAGIC)
    {
        halt();
    }

    mbi = (multiboot_info_t*)address;
    init_gfx(mbi);
}


void kernel_start() 
{
    gfx_color_t test_color;
    test_color.b = 0xFF;

    uint32_t height = gfx_get_height();
    uint32_t width  = gfx_get_width();


    for(uint32_t y = 0; y < height; y++)
    {
        for(uint32_t x = 0; x < width; x++)
        {
            float c = (float)y / (float)height;
            int8_t color = (int8_t)(c * 255.0);

            test_color.g = color;   
            test_color.r = 255 - color;

            gfx_draw_pixel(x, y, test_color);
        }
    }
}
