#include "gui.h"

#include <stdbool.h>

#define MAX_BUTTONS 20

static gui_button_t buttons[MAX_BUTTONS];
static bool buttons_pressed[MAX_BUTTONS] = {false};

static uint8_t buttons_size = 0;

static bool intersects(gfx_rect_2d_t rect, int16_t x, int16_t y)
{
    return x <= (rect.x + rect.width / 2) && x >= (rect.x - rect.width / 2) && y <= (rect.y + rect.height / 2) && y >= (rect.y - rect.height / 2);
}

void register_button(const gui_button_t* button)
{
    buttons[buttons_size++] = *button;
}

void gui_update()
{
    for(uint8_t i = 0; i < buttons_size; i++)
    {

    }
}


void gui_mouse_click_callback(int16_t x, int16_t y)
{
    for(uint8_t i = 0; i < buttons_size; i++)
    {

    }
}
