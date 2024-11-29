#pragma once 

#include "Kernel/gfx.h"

#include <stdint.h>


typedef void (*gui_button_fn_t)();

typedef struct {
    gfx_rect_2d_t   rect;
    gui_button_fn_t callback;
    const char*     label;
} gui_button_t;

void register_button(const gui_button_t* button);

void gui_update();
void gui_mouse_click_callback(int16_t x, int16_t y);