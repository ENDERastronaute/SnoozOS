
#include "headers/idt.h"
#include <stdint.h>

struct IDTEntry {
    uint16_t offset_low;
    uint16_t selector;
    uint8_t zero;
    uint8_t attr;
    uint16_t offset_high;
} __attribute__ ((packed));

struct IDTR {
    uint16_t limit;
    uint32_t base;
} __attribute__ ((packed));

IDTEntry idt[256];

void set_idt_entry(uint8_t idx, void* handler, uint8_t dpl) {
    uintptr_t addr = (uintptr_t) handler;

    IDTEntry* entry = &idt[idx];

    entry->offset_low = addr & 0xFFFF;
    entry->offset_high = (addr >> 16) & 0xFFFF;
    entry->selector = 0x08;
    entry->zero = 0x0;
    entry->attr = 0b1110 | ((dpl & 0b11) << 5) | (1 << 7);
}

extern char vector_0_handler[];

void load_idt(void* addr) {
    IDTR idt_reg;
    idt_reg.limit = 256 * 8 - 1;
    idt_reg.base = (uint32_t) addr;

    __asm__ volatile ("lidt %0" :: "m"(idt_reg));
}

void init_IDT() {
    for (int i = 0; i < 256; i++) {
        set_idt_entry(i, (void*) ((uintptr_t) vector_0_handler + (i * 8)), 0b00);
    }

    load_idt(&vector_0_handler);
}

// int idx = 0;
//
// void set_entry(uintptr_t base, uint16_t selector, uint8_t attr) {
//     idt[idx].offset_low = base & 0xFFFF;
//     idt[idx].selector = selector;
//     idt[idx].zero = 0;
//     idt[idx].attr = attr;
//     idt[idx].offset_high = (base >> 16) & 0xFFFF;
//
//     idx++;
// }
//
// void init_IDT(uint8_t code_seg, uint8_t data_seg) {
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) keyboard_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
// }
// int idx = 0;
//
// void set_entry(uintptr_t base, uint16_t selector, uint8_t attr) {
//     idt[idx].offset_low = base & 0xFFFF;
//     idt[idx].selector = selector;
//     idt[idx].zero = 0;
//     idt[idx].attr = attr;
//     idt[idx].offset_high = (base >> 16) & 0xFFFF;
//
//     idx++;
// }
//
// void init_IDT(uint8_t code_seg, uint8_t data_seg) {
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) keyboard_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
//     set_entry((uintptr_t) placeholder_handler, code_seg, 0x8E);
// }