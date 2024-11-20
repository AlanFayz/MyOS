#include "gdt.h"

#define GDT_DESCRIPTOR_ENTRY_SIZE 5

static gdt_descriptor_entry_t   gdt_descriptor_entries[GDT_DESCRIPTOR_ENTRY_SIZE];
static gdt_descriptor_pointer_t gdt_descriptor_pointer;

void create_null_gdt_entry(uint8_t index)
{
    gdt_descriptor_entries[index].segment_limit_low      = 0;
    gdt_descriptor_entries[index].segment_limit_high     = 0; 
    gdt_descriptor_entries[index].segment_address_low    = 0;
    gdt_descriptor_entries[index].segment_address_middle = 0;
    gdt_descriptor_entries[index].segment_address_high   = 0;
    gdt_descriptor_entries[index].segment_type           = 0; 
    gdt_descriptor_entries[index].descriptor_type        = 0; 
    gdt_descriptor_entries[index].descriptor_privilege_level = 0; 
    gdt_descriptor_entries[index].present                = 0; 
    gdt_descriptor_entries[index].available              = 0; 
    gdt_descriptor_entries[index].reserved               = 0; 
    gdt_descriptor_entries[index].size                   = 0; 
    gdt_descriptor_entries[index].granularity            = 0; 
}

void create_gdt_entry(uint8_t index, uint32_t limit, uint32_t address, uint8_t access, uint8_t flags)
{
    gdt_descriptor_entries[index].segment_address_low    = address & 0xFFFF;
    gdt_descriptor_entries[index].segment_address_middle = (address >> 16) & 0xFF;
    gdt_descriptor_entries[index].segment_address_high   = (address >> 24) & 0xFF;

    gdt_descriptor_entries[index].segment_limit_low      = limit & 0xFFFF;
    gdt_descriptor_entries[index].segment_limit_high     = (limit >> 16) & 0x0F;

    gdt_descriptor_entries[index].segment_type           = access & 0x0F;
    gdt_descriptor_entries[index].descriptor_type        = (access >> 4) & 0x01;
    gdt_descriptor_entries[index].descriptor_privilege_level = (access >> 5) & 0x03;
    gdt_descriptor_entries[index].present                = (access >> 7) & 0x01;

    gdt_descriptor_entries[index].granularity            = (flags >> 3) & 0x01;
    gdt_descriptor_entries[index].size                   = (flags >> 2) & 0x01;
    gdt_descriptor_entries[index].reserved               = 0;
    gdt_descriptor_entries[index].available              = flags & 0x01;
}

extern void gdt_flush(uint32_t);

void init_gdt()
{
    gdt_descriptor_pointer.limit = sizeof(gdt_descriptor_entry_t) * GDT_DESCRIPTOR_ENTRY_SIZE - 1;
    gdt_descriptor_pointer.base = &gdt_descriptor_entries;

    create_null_gdt_entry(0);
    create_gdt_entry(1, 0xFFFFFFFF, 0, 0x9A, 0xCF); //kernel code segment
    create_gdt_entry(2, 0xFFFFFFFF, 0, 0x92, 0xCF); //kernel data segment
    create_gdt_entry(3, 0xFFFFFFFF, 0, 0xFA, 0xCF); //user code segment
    create_gdt_entry(4, 0xFFFFFFFF, 0, 0xF2, 0xCF); //user data segment

    gdt_flush(&gdt_descriptor_pointer);
}