
#ifndef ISR_H
#define ISR_H

#include <stdint.h>
#include "../../../drivers/input/headers/keyboard.h"


// struct interrupt_frame;
//
// void save_reg() __attribute__ ((no_caller_saved_registers ()));
//
// void restore_reg() __attribute__ ((no_caller_saved_registers ()));
//
// __attribute__ ((interrupt)) void placeholder_handler(struct interrupt_frame* frame);
//
// __attribute__ ((interrupt)) void keyboard_handler(struct interrupt_frame* frame);

extern "C" void interrupt_dispatch(uint32_t error_code, uint32_t vector);

#endif // !ISR_H
