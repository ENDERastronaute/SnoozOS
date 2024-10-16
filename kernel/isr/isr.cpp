

#include "headers/isr.h"

extern "C" void interrupt_dispatch(uint32_t error_code, uint32_t vector) {
    switch (vector) {
        case 0x21:
            keyboard_interrupt(); // general protection fault
            break;
        default:
            break;
    }
}

//__attribute__((no_caller_saved_registers)) void save_reg() {
//    __asm__("pusha");
//}
//
//__attribute__ ((no_caller_saved_registers)) void restore_reg() {
//    __asm__("popa");
//}
//
//__attribute__ ((interrupt)) void placeholder_handler(struct interrupt_frame* frame) {
//
//}
//
//__attribute__ ((interrupt)) void keyboard_handler(struct interrupt_frame* frame) {
//    save_reg();
//
//    uint8_t scancode = port_byte_in(0x60);
//
//    restore_reg();
//}
