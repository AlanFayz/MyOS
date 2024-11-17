#pragma once

#include <stdint.h>

typedef struct {
    uint32_t ip;
    uint32_t cs;
    uint32_t flags;
    uint32_t sp;
    uint32_t ss;
} interrupt_frame_t __attribute__((packed));

//programmable interval timer

void pit_init(uint32_t frequency);
uint16_t read_pit_count();
void set_pit_count(uint16_t count);

void irq0_handler(interrupt_frame_t* ptr);