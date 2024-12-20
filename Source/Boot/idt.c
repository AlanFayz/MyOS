#include "idt.h"

#include "Common/cpu.h"
#include "Common/memory.h"

#include "Common/Interrupts/isr.h"

#define DESCRIPTOR_TABLE_COUNT 256

static interrupt_descriptor_table_entry   idt_entrys[DESCRIPTOR_TABLE_COUNT];
static interrupt_descriptor_table_pointer idt_pointer;

static void create_idt_entry(int32_t index, uint32_t handler_address, uint16_t selector, uint8_t type_attributes)
{
    if(index >= DESCRIPTOR_TABLE_COUNT)
        return;

    idt_entrys[index].offset_1 = handler_address & 0xFFFF;
    idt_entrys[index].offset_2 = (handler_address >> 16) & 0xFFFF;
    idt_entrys[index].type_attributes = type_attributes | 0x60;
    idt_entrys[index].selector = selector;
    idt_entrys[index].zero  = 0;
}

// programmable interrupt computer
static void init_pic()
{
    port_byte_out(PIC1, PIC_INIT_MODE); 
    port_byte_out(PIC2, PIC_INIT_MODE); 

    port_byte_out(PIC1_DATA, PIC1_OFFSET);
    port_byte_out(PIC2_DATA, PIC2_OFFSET);

    port_byte_out(PIC1_DATA, PIC_ICW3_SLAVE_ON_IRQ2); 
    port_byte_out(PIC2_DATA, PIC_ICW3_SLAVE_IDENTITY); 

    port_byte_out(PIC1_DATA, PIC_MODE_8086);
    port_byte_out(PIC2_DATA, PIC_MODE_8086);

    port_byte_out(PIC1_DATA, PIC_MASK);
    port_byte_out(PIC2_DATA, PIC_MASK);
}

static void setup_interrupt_service_routine_entrys()
{
    const uint8_t flags = IDT_FLAG_PRESENT | IDT_FLAG_32_BIT_INTERRUPT_GATE;

    create_idt_entry(0,  (uint32_t)isr0,  IDT_FLAG_CODE_SEGMENT, flags);
    create_idt_entry(1,  (uint32_t)isr1,  IDT_FLAG_CODE_SEGMENT, flags);
    create_idt_entry(2,  (uint32_t)isr2,  IDT_FLAG_CODE_SEGMENT, flags);
    create_idt_entry(3,  (uint32_t)isr3,  IDT_FLAG_CODE_SEGMENT, flags);
    create_idt_entry(4,  (uint32_t)isr4,  IDT_FLAG_CODE_SEGMENT, flags);
    create_idt_entry(5,  (uint32_t)isr5,  IDT_FLAG_CODE_SEGMENT, flags);
    create_idt_entry(6,  (uint32_t)isr6,  IDT_FLAG_CODE_SEGMENT, flags);
    create_idt_entry(7,  (uint32_t)isr7,  IDT_FLAG_CODE_SEGMENT, flags);
    create_idt_entry(8,  (uint32_t)isr8,  IDT_FLAG_CODE_SEGMENT, flags);
    create_idt_entry(9,  (uint32_t)isr9,  IDT_FLAG_CODE_SEGMENT, flags);
    create_idt_entry(10, (uint32_t)isr10, IDT_FLAG_CODE_SEGMENT, flags);
    create_idt_entry(11, (uint32_t)isr11, IDT_FLAG_CODE_SEGMENT, flags);
    create_idt_entry(12, (uint32_t)isr12, IDT_FLAG_CODE_SEGMENT, flags);
    create_idt_entry(13, (uint32_t)isr13, IDT_FLAG_CODE_SEGMENT, flags);
    create_idt_entry(14, (uint32_t)isr14, IDT_FLAG_CODE_SEGMENT, flags);
    create_idt_entry(15, (uint32_t)isr15, IDT_FLAG_CODE_SEGMENT, flags);
    create_idt_entry(16, (uint32_t)isr16, IDT_FLAG_CODE_SEGMENT, flags);
    create_idt_entry(17, (uint32_t)isr17, IDT_FLAG_CODE_SEGMENT, flags);
    create_idt_entry(18, (uint32_t)isr18, IDT_FLAG_CODE_SEGMENT, flags);
    create_idt_entry(19, (uint32_t)isr19, IDT_FLAG_CODE_SEGMENT, flags);
    create_idt_entry(20, (uint32_t)isr20, IDT_FLAG_CODE_SEGMENT, flags);
    create_idt_entry(21, (uint32_t)isr21, IDT_FLAG_CODE_SEGMENT, flags);
    create_idt_entry(22, (uint32_t)isr22, IDT_FLAG_CODE_SEGMENT, flags);
    create_idt_entry(23, (uint32_t)isr23, IDT_FLAG_CODE_SEGMENT, flags);
    create_idt_entry(24, (uint32_t)isr24, IDT_FLAG_CODE_SEGMENT, flags);
    create_idt_entry(25, (uint32_t)isr25, IDT_FLAG_CODE_SEGMENT, flags);
    create_idt_entry(26, (uint32_t)isr26, IDT_FLAG_CODE_SEGMENT, flags);
    create_idt_entry(27, (uint32_t)isr27, IDT_FLAG_CODE_SEGMENT, flags);
    create_idt_entry(28, (uint32_t)isr28, IDT_FLAG_CODE_SEGMENT, flags);
    create_idt_entry(29, (uint32_t)isr29, IDT_FLAG_CODE_SEGMENT, flags);
    create_idt_entry(30, (uint32_t)isr30, IDT_FLAG_CODE_SEGMENT, flags);
    create_idt_entry(31, (uint32_t)isr31, IDT_FLAG_CODE_SEGMENT, flags);
    
    create_idt_entry(32, (uint32_t)irq0,  IDT_FLAG_CODE_SEGMENT, flags);
    create_idt_entry(33, (uint32_t)irq1,  IDT_FLAG_CODE_SEGMENT, flags);
    create_idt_entry(34, (uint32_t)irq2,  IDT_FLAG_CODE_SEGMENT, flags);
    create_idt_entry(35, (uint32_t)irq3,  IDT_FLAG_CODE_SEGMENT, flags);
    create_idt_entry(36, (uint32_t)irq4,  IDT_FLAG_CODE_SEGMENT, flags);
    create_idt_entry(37, (uint32_t)irq5,  IDT_FLAG_CODE_SEGMENT, flags);
    create_idt_entry(38, (uint32_t)irq6,  IDT_FLAG_CODE_SEGMENT, flags);
    create_idt_entry(39, (uint32_t)irq7,  IDT_FLAG_CODE_SEGMENT, flags);
    create_idt_entry(40, (uint32_t)irq8,  IDT_FLAG_CODE_SEGMENT, flags);
    create_idt_entry(41, (uint32_t)irq9,  IDT_FLAG_CODE_SEGMENT, flags);
    create_idt_entry(42, (uint32_t)irq10, IDT_FLAG_CODE_SEGMENT, flags);
    create_idt_entry(43, (uint32_t)irq11, IDT_FLAG_CODE_SEGMENT, flags);
    create_idt_entry(44, (uint32_t)irq12, IDT_FLAG_CODE_SEGMENT, flags);
    create_idt_entry(45, (uint32_t)irq13, IDT_FLAG_CODE_SEGMENT, flags);
    create_idt_entry(46, (uint32_t)irq14, IDT_FLAG_CODE_SEGMENT, flags);
    create_idt_entry(47, (uint32_t)irq15, IDT_FLAG_CODE_SEGMENT, flags);


    create_idt_entry(128, (uint32_t)isr128, IDT_FLAG_CODE_SEGMENT, flags);
    create_idt_entry(177, (uint32_t)isr177, IDT_FLAG_CODE_SEGMENT, flags);
}


extern void idt_flush(uint32_t);

void init_idt()
{
    idt_pointer.limit = sizeof(interrupt_descriptor_table_entry) * DESCRIPTOR_TABLE_COUNT - 1;
    idt_pointer.base  = (uint32_t)&idt_entrys;

    init_pic();
    setup_interrupt_service_routine_entrys();
    idt_flush((uint32_t)&idt_pointer);
}