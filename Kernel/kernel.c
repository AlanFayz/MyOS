#include "../Drivers/screen.h"
#include "../Drivers/input.h"

#include "memory.h"

#define true 1
#define false 0

void main()
{
    screen_clear(0x00);

    while(true)
    {
      	if(key_detected())
    	{
            key_t key = get_key();

            if(key.pressed)
                screen_put_char(key.scancode_ascii, 0x0);

    	}
    }
}


