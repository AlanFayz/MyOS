#include "gdt.h"

#define GDT_DESCRIPTOR_ENTRY_SIZE 6

#include "Common/memory.h"

static gdt_descriptor_entry_t   gdt_descriptor_entries[GDT_DESCRIPTOR_ENTRY_SIZE];
static gdt_descriptor_pointer_t gdt_descriptor_pointer;
static tss_entry_t tss_entry;

extern void gdt_flush(uint32_t);
extern void tss_flush();

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

    gdt_descriptor_entries[index].granularity   = (flags >> 3) & 0x01;
    gdt_descriptor_entries[index].size          = (flags >> 2) & 0x01;
    gdt_descriptor_entries[index].reserved      = 0;
    gdt_descriptor_entries[index].available     = flags & 0x01;
}

void write_tss(uint32_t index, uint32_t ss0, uint32_t esp0)
{
    uint32_t base = (uint32_t)&tss_entry;
    uint32_t limit = base + sizeof(tss_entry);

    create_gdt_entry(index, base, limit, 0xE9, 0);
    memset(&tss_entry, 0, sizeof(tss_entry));

    tss_entry.ss0  = ss0;
    tss_entry.esp0 = esp0;

    tss_entry.cs = 0x08 | 0x3;
    tss_entry.ss = tss_entry.ds = tss_entry.es = tss_entry.fs = tss_entry.gs = 0x10 | 0x3;
    tss_entry.iomap_base = sizeof(tss_entry);
}

void init_gdt()
{
    gdt_descriptor_pointer.limit = sizeof(gdt_descriptor_entry_t) * GDT_DESCRIPTOR_ENTRY_SIZE - 1;
    gdt_descriptor_pointer.base = &gdt_descriptor_entries;

    create_null_gdt_entry(0);
    create_gdt_entry(1, 0xFFFFFFFF, 0, 0x9A, 0xCF); //kernel code segment
    create_gdt_entry(2, 0xFFFFFFFF, 0, 0x92, 0xCF); //kernel data segment
    create_gdt_entry(3, 0xFFFFFFFF, 0, 0xFA, 0xCF); //user code segment
    create_gdt_entry(4, 0xFFFFFFFF, 0, 0xF2, 0xCF); //user data segment
    write_tss(5, 0x10, 0);

    gdt_flush(&gdt_descriptor_pointer);
    tss_flush();
}