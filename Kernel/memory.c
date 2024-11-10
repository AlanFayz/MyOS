#include "memory.h"

void memcpy(void* destination, const void* source, uint32_t size)
{
    for (uint32_t i = 0; i < size; i++)
          *((uint8_t*)destination + i) = *((uint8_t*)source + i);
}

