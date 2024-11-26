#include "print.h"

#define SPACING 25

static gfx_character_t default_character = {
    .character = ' ',
    .width  = 25,
    .height = 25,
};

void print_char(int16_t x, int16_t y, gfx_color_t color, char value)
{
    default_character.x = x;
    default_character.y = y; 
    default_character.character = value;

    gfx_draw_character(default_character, color);
}

void print_float(int16_t x, int16_t y, gfx_color_t color, int8_t dp, double value)
{
    int32_t integer = (int32_t)value;
    x = print_int(x, y, color, integer);

    value -= (double)integer;  //we are only left with the decimal part

    print_char(x, y, color, '.');
    x += SPACING;

    while(value != 0 && dp > 0)
    {
        value *= 10;

        print_char(x, y, color, (char)value + '0');
        x += 30;

        value -= (int32_t)value;
        dp--;
    }
}

void print(int16_t x, int16_t y, gfx_color_t color, const char *value)
{
    for(; *value != '\0'; value++)
    {
        print_char(x, y, color, *value);
        x += SPACING;
    }
}

int8_t print_int(int16_t x, int16_t y, gfx_color_t color, int32_t value)
{
    if(value == 0)
    {
        print_char(x, y, color, '0');
        x += SPACING;
        return;
    }

    if(value < 0)
    {
    	print_char(x, y, color, '-');
        x += SPACING;
        value = -value;
    }

    int8_t digits[10] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1};

    uint32_t index = 0;
    while(value >= 1 && index < 10)
    {
          int8_t remainder = (value % 10);
          value /= 10;

          digits[index++] = remainder;
    }

    for(int8_t i = 9; i >= 0; --i)
    {
        if(digits[i] == -1)
            continue;

        char character = digits[i] + '0';
        print_char(x, y, color, character);
        x += SPACING;
    }

    return x;
}

void print_bin(int16_t x, int16_t y, gfx_color_t color, uint32_t value)
{
    uint32_t bit_count = 32;

    while(bit_count > 0)
    {
        bit_count -= 1;
        uint32_t temp = value >> bit_count;
        temp &= 0x1;

        char val = (char)temp + '0';
        print_char(x, y, color, val);
        x += SPACING;
    }
}

void print_hex(int16_t x, int16_t y, gfx_color_t color, uint32_t value)
{
    uint32_t bit_count = 32;

    while(bit_count > 0)
    {
          bit_count -= 4;
          uint32_t temp = value >> bit_count;
          temp &= 0xF;

          char val = 0;
          if(temp < 10)
          {
              val = (char)temp + '0';
          }
          else
          {
             val = (char)temp + 'A' - 10;
          }

          print_char(x, y, color, val);
          x += SPACING;
    }
}