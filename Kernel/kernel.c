#include "../Drivers/screen.h"

void main()
{
    screen_clear(0x00);
    screen_print_string("wot!!!", 0xB0);
}


