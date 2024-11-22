#include "multiboot.h"
#include "gfx.h"
#include "System/timer.h"

#include <stdint.h>

void init_kernel(uint32_t magic, uint32_t address)
{
    multiboot_info_t* mbi;

    if(magic != MULTIBOOT_BOOTLOADER_MAGIC)
    {
        halt();
    }

    mbi = (multiboot_info_t*)address;

    init_gfx(mbi);
    init_system_timer();
}


