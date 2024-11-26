#pragma once 

#include <stdint.h>

typedef enum {
    IDT_FLAG_PRESENT   = 0x80, 
    IDT_FLAG_32_BIT_INTERRUPT_GATE = 0x0E, 
    IDT_FLAG_CODE_SEGMENT = 0x08
} idt_flags_t;

typedef enum {
    PIC1           = 0x20,  
    PIC1_DATA      = 0x21, 
    PIC2           = 0xA0,  
    PIC2_DATA      = 0xA1, 
    PIC_INIT_MODE  = 0x11, 
    PIC_MODE_8086  = 0x01, 
    PIC1_OFFSET    = 0x20,
    PIC2_OFFSET    = 0x28, 
    PIC_ICW3_SLAVE_ON_IRQ2 = 0x04,
    PIC_ICW3_SLAVE_IDENTITY = 0x02,
    PIC_MASK = 0
} pic_t;

uint8_t  port_byte_in(uint16_t port);
uint16_t port_word_in(uint16_t port);
void port_byte_out(uint16_t port,  uint8_t data);
void port_word_out(uint16_t port, uint16_t data);

void panic();
void sti();
void cli();
void hlt();