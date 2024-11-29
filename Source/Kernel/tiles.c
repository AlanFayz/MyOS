#include "tiles.h"

#include "gfx.h"


#define WIDTH  100 // * 32
#define BITS   32
#define HEIGHT 100

//don't like set sizes but i still haven't made malloc

static uint32_t tiles[WIDTH * HEIGHT] = {0};

static uint32_t tile_width  = 10;
static uint32_t tile_height = 10;

void set_tile(uint32_t x, uint32_t y)
{
    uint32_t x_remainder = x % BITS;

    uint32_t index = (x / BITS) + y * WIDTH;
    
    if(index >= sizeof(tiles) / sizeof(tiles[0]))
    {
        return;
    }

    tiles[index] |= (1 << x_remainder);
}

void set_tile_dimensions(uint16_t width, uint16_t height)
{
    tile_width  = width;
    tile_height = height;
}

void remove_tile(uint32_t x, uint32_t y)
{
    uint32_t x_remainder = x % BITS;

    uint32_t index = (x / BITS) + y * WIDTH;
    
    if(index >= sizeof(tiles) / sizeof(tiles[0]))
    {
        return;
    }


     tiles[index] &= ~(1 << x_remainder); 
}

bool is_tile_set(uint32_t x, uint32_t y)
{
    uint32_t x_remainder = x % BITS;

    uint32_t index = (x / BITS) + y * WIDTH;
    
    if(index >= sizeof(tiles) / sizeof(tiles[0]))
    {
        return;
    }

    return tiles[index] & (1 << x_remainder);
}

void render_tiles()
{
    gfx_rect_2d_t rect;

    rect.width  = tile_width;
    rect.height = tile_height;

    gfx_color_t color = {0xFF, 0xFF, 0xFF};

    for(uint32_t y = 0; y < HEIGHT; y++)
    {
        rect.y = y * tile_height;

        for(uint32_t x = 0; x < WIDTH; x++)
        {
            uint32_t index = x + y * WIDTH;

            if(!tiles[index])
                continue;

            for(uint8_t shft = 0; shft < BITS; shft++)
            {
                rect.x = (x + shft) * tile_width;
                
                if(tiles[index] & (1 << (shft)))
                {
                    gfx_draw_rect(rect, color);
                }
            }
        }
    }
}
