#include <stdint.h>
#include <stdbool.h>

#include "System/timer.h"
#include "System/print.h"
#include "System/keyboard.h"

#include "Common/cpu.h"

#include "gfx.h"

void kernel_start() 
{
    gfx_color_t color = {0xFF, 0xAA, 0};
    
    int x = 0;
    int y = 0;

    for(;;)
    {
        sleep(5);
        print(300, 200, color, "0 key pressed");
    }
}


