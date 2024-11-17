#pragma once

#include "../bool.h"


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

typedef enum {
    IDT_FLAG_PRESENT   = 0x80, 
    IDT_FLAG_32_BIT_INTERRUPT_GATE = 0x0E, 
    IDT_FLAG_CODE_SEGMENT = 0x08
} IDT_FLAGS;

typedef enum {
    PIC_COMMAND_0 = 0x20,  //first programmable interface computer
    PIC_DATA_0    = 0x21, 
    PIC_COMMAND_1 = 0xA0,  //second 
    PIC_DATA_1    = 0xA1, 
    PIC_INIT_MODE = 0x11
} PIC;

void idt_init();