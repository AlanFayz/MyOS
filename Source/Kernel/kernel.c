#include <stdint.h>
#include <stdbool.h>

#include "System/timer.h"
#include "System/print.h"
#include "System/keyboard.h"
#include "System/mouse.h"
#include "tiles.h"

#include "Common/cpu.h"

#include "gfx.h"

void kernel_start() 
{
    gfx_color_t color = {0xFF, 0xAA, 0};
    gfx_color_t black = {0, 0, 0};

    set_tile(20, 70);
    set_tile(10, 40);

    for(;;)
    {
        gfx_swap_buffers();
        gfx_clear(black);

        print_int(300, 300, color, mouse_get_y());
        render_tiles();
    }
}


