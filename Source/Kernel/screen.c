#include "screen.h"

#include "Common/memory.h"

#include <stdarg.h>

#define VGA_ADDRESS 0xB8000

static screen_t screen = {
      .framebuffer = (uint8_t*)VGA_ADDRESS,
      .rows = 20,
      .columns = 80,
      .cursor = {0, 0},
      .white_on_black = 0x0F
};

static void display_byte(int8_t character, uint32_t col, uint32_t row, color_t color)
{
    if (col >= screen.columns || row >= screen.rows)
        return;

    uint8_t* memory = screen.framebuffer;

    color = color ? color : screen.white_on_black;

    uint32_t offset = (row * screen.columns + col) * 2;

    memory[offset] = character;
    memory[offset + 1] = color;
}

void cursor_set(uint32_t row, uint32_t col)
{
    if (col >= screen.columns || row >= screen.rows)
        return;

    screen.cursor.row = row;
    screen.cursor.column = col;

    uint32_t index = row * screen.columns + col;

    port_byte_out(SCREEN_CONTROL_IO_PORT, 14);
    port_byte_out(SCREEN_DATA_IO_PORT, (index >> 8) & 0xFF);
    port_byte_out(SCREEN_CONTROL_IO_PORT, 15);
    port_byte_out(SCREEN_DATA_IO_PORT, index & 0xFF);
}

uint32_t cursor_get_index()
{
    port_byte_out(SCREEN_CONTROL_IO_PORT,   14);
    uint32_t offset = (uint32_t)(port_byte_in(SCREEN_DATA_IO_PORT) << 8);
    port_byte_out(SCREEN_CONTROL_IO_PORT , 15);
    offset += (uint32_t)port_byte_in(SCREEN_DATA_IO_PORT);
    return offset * 2;
}

void cursor_increment()
{
      screen.cursor.column++;
      if(screen.cursor.column >= screen.columns)
      {
          screen.cursor.row++;
          //screen_shift_up();


          if(screen.cursor.row >= screen.rows)
          {
             screen.cursor.row--;
          }
      }

      screen.cursor.column %= screen.columns;

      cursor_set(screen.cursor.row, screen.cursor.column);
}

void screen_clear(color_t color)
{
    for(uint16_t i = 0; i < screen.rows; i++)
    {
          for(uint16_t j = 0; j < screen.columns; j++)
          {
              display_byte(' ', j, i, color);
          }
    }

    cursor_set(0, 0);
}

cursor_t screen_get_cursor()
{
    return screen.cursor;
}

void screen_put_char(int8_t c, color_t color)
{
   if (c == '\n')
    {
        cursor_set(screen.cursor.row + 1, 0);
        return;
    }

    display_byte(c, screen.cursor.column, screen.cursor.row, color);
    cursor_increment();
}

void screen_put_int(int32_t value, color_t color)
{
    if(value == 0)
    {
        screen_put_char('0', color);
        return;
    }

    if(value < 0)
    {
    	screen_put_char('-', color);
        value = -value;
    }

    int32_t digits[10] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1};

    uint32_t index = 0;
    while(value >= 1 && index < 10)
    {
          int32_t remainder = value % 10;
          value /= 10;

          digits[index++] = remainder;
    }

    for(int32_t i = 9; i >= 0; --i)
    {
        if(digits[i] == -1)
            continue;

        char character = digits[i] + '0';
        screen_put_char(character, color);
    }
}

void screen_put_hex(uint32_t value, color_t color)
{
    uint32_t bit_count = 32;

    while(bit_count > 0)
    {
          bit_count -= 4;
          uint32_t temp = value >> bit_count;
          temp &= 0x0000000F;

          char val = 0;
          if(temp < 10)
          {
              val = (char)temp + '0';
          }
          else
          {
             val = (char)temp + 'A' - 10;
          }

          screen_put_char(val, color);
    }
}

void screen_put_bin(uint32_t value, color_t color)
{
    uint32_t bit_count = 32;

    while(bit_count > 0)
    {
        bit_count -= 1;
        uint32_t temp = value >> bit_count;
        temp &= 0x1;

        char val = (char)temp + '0';
        screen_put_char(val, color);
    }
}

void screen_print_string(const char* str, color_t color)
{
    for(; *str != '\0'; str++)
    {
        screen_put_char(*str, color);
    }

}

void screen_shift_down()
{
    for(uint16_t col = 0; col < screen.columns; col++)
    {
        display_byte(' ', col, 0, 0x00);
    }

    for (int32_t row = (int32_t)screen.rows - 1; row > 0; row--)
    {
        memcpy(screen.framebuffer + (row * screen.columns) * 2,
               screen.framebuffer + ((row - 1) * screen.columns) * 2,
               screen.columns * 2);
    }
}

void screen_shift_up()
{
    for(uint16_t col = 0; col < screen.columns; col++)
    {
        display_byte(' ', col, screen.rows - 1, 0x00);
    }

    for (int32_t row = 1; row < screen.rows; row++)
    {
        memcpy(screen.framebuffer + ((row - 1) * screen.columns) * 2,
               screen.framebuffer + (row  * screen.columns) * 2,
               screen.columns * 2);
    }
}

void printf(const char* fmt, ...)
{
    va_list va_ptr;
    va_start(va_ptr, fmt);

    for(char* ptr = fmt; *ptr != '\0'; ptr++)
    {
        if(*ptr != '%')
        {
            screen_put_char(*ptr, 0);
            continue;
        }

        char next = *(++ptr);

        switch (next)
        {
            case 'i':
            {
                int32_t arg = va_arg(va_ptr, int);
                screen_put_int(arg, 0);
                break;
            }
            case 's':
            {
                const char* arg = va_arg(va_ptr, const char*);
                screen_print_string(arg, 0);
                break;
            }
            case 'b':
            {
                uint32_t arg = va_arg(va_ptr, uint32_t);
                screen_put_bin(arg, 0);
                break;
            }
            case 'h':
            {
                uint32_t arg = va_arg(va_ptr, uint32_t);
                screen_put_hex(arg, 0);
                break;
            }
            case 'c':
            {
                char arg = (char)va_arg(va_ptr, int);
                screen_put_char(arg, 0);
                break;
            }
            default:
                break;
        }
    }

    va_end(va_ptr);
}
