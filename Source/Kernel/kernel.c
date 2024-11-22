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
    test_color.g = 0xFF;
    test_color.r = 0x00;

    gfx_rect_2d_t rect;
    rect.x = 800;
    rect.y = 300;
    rect.width = 200;
    rect.height = 200;

    gfx_draw_rect(rect, test_color);
    
    gfx_circle_t circle;
    circle.x = 300;
    circle.y = 300;
    circle.radius = 100;

    gfx_draw_circle(circle, test_color);

    gfx_character_t character;

    character.character = 'A';
    character.x = 50;
    character.y = 50;

    gfx_draw_character(character, test_color);
}
