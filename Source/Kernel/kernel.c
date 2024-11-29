#include <stdint.h>
#include <stdbool.h>

#include "System/timer.h"
#include "System/print.h"
#include "System/keyboard.h"
#include "System/mouse.h"
#include "tiles.h"

#include "Common/cpu.h"

#include "gfx.h"

//game of life simulations rules here: https://playgameoflife.com/
void simulate();

void kernel_start() 
{
    gfx_color_t color = {0xFF, 0xAA, 0};
    gfx_color_t black = {0, 0, 0};

    set_tile(10, 5); set_tile(10, 6); set_tile(10, 7);
    set_tile(12, 5); set_tile(12, 6); set_tile(12, 7);
    set_tile(16, 5); set_tile(16, 6); set_tile(16, 7);
    set_tile(14, 5); set_tile(14, 6); set_tile(14, 7);
    set_tile(10, 9); set_tile(10, 10); set_tile(10, 11);
    set_tile(12, 9); set_tile(12, 10); set_tile(12, 11);
    set_tile(16, 9); set_tile(16, 10); set_tile(16, 11);
    set_tile(14, 9); set_tile(14, 10); set_tile(14, 11);

    double start = system_timer_get_ticks_seconds();

    for(;;)
    {
        gfx_swap_buffers();
        gfx_clear(black);

        if(system_timer_get_ticks_seconds() - start >= 1)
        {
            simulate();
            start = system_timer_get_ticks_seconds();
        }

        render_tiles();
        draw_cursor();
    }
}


void simulate()
{
    for(uint16_t y = 0; y < 50; y++)
    {
        for(uint16_t x = 0; x < 50; x++)
        {
            uint8_t neighbor_count = 0;

            for(int16_t dy = y - 1; dy <= y + 1; dy++)
            {
                if(dy < 0)
                {
                    continue;
                }

                for(int16_t dx = x - 1; dx <= x + 1; dx++)
                {
                    if(dx < 0)
                    {
                        continue;
                    }

                    if(dx == x && dy == y)
                    {
                        continue;
                    }

                    if(is_tile_set(dx, dy))
                    {
                        neighbor_count++;
                    }
                }
            }

            //For a space that is empty

            if(!is_tile_set(x, y))
            {
                if(neighbor_count == 3)
                {
                    set_tile(x, y);
                }

                continue;
            }

            //Each cell with one or no neighbors dies.

            if(neighbor_count <= 1)
            {
                remove_tile(x, y);
                continue;
            }

            //Each cell with four or more neighbors dies.

            if(neighbor_count >= 4)
            {
                remove_tile(x, y);
                continue;
            }

            //Each cell with two or three neighbors survives...
            set_tile(x, y);
        }
    }
}



