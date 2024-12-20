#include "memory.h"

void memcpy(void* destination, const void* source, uint32_t size)
{
    for (uint32_t i = 0; i < size; i++)
          *((uint8_t*)destination + i) = *((uint8_t*)source + i);
}

void memset(void* dest, int8_t value, uint32_t size)
{
    int8_t* dest8 = (int8_t*)dest;

    for (uint32_t i = 0; i < size; i++)
      dest8[i] = value;
}

