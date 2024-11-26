#include "multiboot.h"
#include "gfx.h"

#include "System/timer.h"
#include "System/keyboard.h"

#include "Common/cpu.h"


#include <stdint.h>

void init_kernel(uint32_t magic, uint32_t address)
{
    multiboot_info_t* mbi;

    if(magic != MULTIBOOT_BOOTLOADER_MAGIC)
    {
        panic();
    }

    mbi = (multiboot_info_t*)address;

    init_gfx(mbi);
    init_system_timer();
    init_keyboard();
}


