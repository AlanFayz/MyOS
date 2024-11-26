#pragma once

#include <stdint.h>
#include <stdbool.h>

typedef struct {
   uint16_t offset_1;        // offset bits 0..15
   uint16_t selector;        // a code segment selector in GDT or LDT
   uint8_t  zero;            // unused, set to 0
   uint8_t  type_attributes; // gate type, dpl, and p fields
   uint16_t offset_2;        // offset bits 16..31
} __attribute__((packed)) interrupt_descriptor_table_entry;

typedef struct {
    uint16_t limit;        // size
    uint32_t base;         // base address
} __attribute__((packed)) interrupt_descriptor_table_pointer;



