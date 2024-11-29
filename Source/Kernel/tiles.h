#pragma once

#include <stdint.h>
#include <stdbool.h>

void set_tile(uint32_t x, uint32_t y);
void set_tile_dimensions(uint16_t width, uint16_t height);

bool is_tile_set(uint32_t x, uint32_t y);

void render_tiles();
void remove_tile(uint32_t x, uint32_t y);