#pragma once 

#include "isr.h"

typedef void (*irq_callback_t)(const interrupt_frame_t*);

void irq_install_callback(int8_t index, irq_callback_t callback);
void irq_remove_callback(int8_t index);