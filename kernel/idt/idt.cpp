
#include "headers/idt.h"
#include <stdint.h>

#include "../../drivers/output/headers/screen.h"
#include "../../drivers/input/headers/keyboard.h"

const char* e_messages[] = {
    "Division By Zero",
    "Debug",
    "NMI",
    "BP",
    "IDO",
    "OoB",
    "Invalid Opcode",
    "No Coprocessor",
    "DF",
    "CSO",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "GPF",
    "Page Fault",
    "Unknown Interrupt",
    "Alignment Fault",
    "Machine Check",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};

void *irq_routines[16] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0
};

void irq_install_handler(int irq, void (*handler)(struct Interrupt_registers* reg)) {
    irq_routines[irq] = handler;
}

void irq_uninstall_handler(int irq) {
    irq_routines[irq] = 0;
}

void install_IRQs() {
    irq_install_handler(1, &keyboard_interrupt);
}

extern "C" void irq_handler(struct Interrupt_registers* reg) {
    void (*handler)(struct Interrupt_registers* reg);

    handler = irq_routines[reg->vector - 32];

    if (handler) {
        handler(reg);
    }

    if (reg->vector >= 40) {
        port_byte_out(0xA0, 0x20);
    }

    port_byte_out(0x20, 0x20);
}

extern "C" void isr_handler(struct Interrupt_registers* reg) {
    if (reg->vector < 32) {
        print(e_messages[reg->vector]);
        print("\n");
        print("Exception occured! Starting Panic mode.");
        for (;;);
    }
}

struct IDTEntry {
    uint16_t base_low;
    uint16_t selector;
    uint8_t zero;
    uint8_t flags;
    uint16_t base_high;
} __attribute__ ((packed));

struct IDTR {
    uint16_t limit;
    uint32_t base;
} __attribute__ ((packed));

struct IDTEntry idt[256];
struct IDTR idtr;

void set_idt_entry(uint8_t idx, uint32_t base, uint16_t selector, uint8_t flags) {
    idt[idx].base_low = base & 0xFFFF;
    idt[idx].base_high = (base >> 16) & 0xFFFF;
    idt[idx].selector = selector;
    idt[idx].zero = 0x0;
    idt[idx].flags = flags | 0x60;
}

extern "C" {
    extern void isr0();
    extern void isr1();
    extern void isr2();
    extern void isr3();
    extern void isr4();
    extern void isr5();
    extern void isr6();
    extern void isr7();
    extern void isr8();
    extern void isr9();
    extern void isr10();
    extern void isr11();
    extern void isr12();
    extern void isr13();
    extern void isr14();
    extern void isr15();
    extern void isr16();
    extern void isr17();
    extern void isr18();
    extern void isr19();
    extern void isr20();
    extern void isr21();
    extern void isr22();
    extern void isr23();
    extern void isr24();
    extern void isr25();
    extern void isr26();
    extern void isr27();
    extern void isr28();
    extern void isr29();
    extern void isr30();
    extern void isr31();

    extern void irq0();
    extern void irq1();
    extern void irq2();
    extern void irq3();
    extern void irq4();
    extern void irq5();
    extern void irq6();
    extern void irq7();
    extern void irq8();
    extern void irq9();
    extern void irq10();
    extern void irq11();
    extern void irq12();
    extern void irq13();
    extern void irq14();
    extern void irq15();

    extern void isr128();
    extern void isr177();

    extern void irq0();
    extern void irq1();
    extern void irq2();
    extern void irq3();
    extern void irq4();
    extern void irq5();
    extern void irq6();
    extern void irq7();
    extern void irq8();
    extern void irq9();
    extern void irq10();
    extern void irq11();
    extern void irq12();
    extern void irq13();
    extern void irq14();
    extern void irq15();

    extern void idt_flush(uint32_t);
} 

void init_IDT() {
    idtr.limit = sizeof(struct IDTEntry) * 256 - 1;
    idtr.base = (uint32_t) &idt;

    memset(&idt, 0, sizeof(IDTEntry) * 256);
    
    // PIC programming
    port_out_b(0x20, 0x11);
    port_out_b(0xA0, 0x11);
    port_out_b(0x21, 0x20);
    port_out_b(0xA1, 0x28);
    port_out_b(0x21, 0x04);
    port_out_b(0xA1, 0x02);
    port_out_b(0x21, 0x01);
    port_out_b(0xA1, 0x01);
    port_out_b(0x21, 0x0);
    port_out_b(0xA1, 0x0);
    
    // exceptions
    set_idt_entry(0, (uint32_t)isr0, 0x08, 0x8E); // 0x8E -> 1000 1110 -> P+DPL+0 GATE | 0x08 -> code segment
    set_idt_entry(1, (uint32_t)isr1, 0x08, 0x8E);
    set_idt_entry(2, (uint32_t)isr2, 0x08, 0x8E);
    set_idt_entry(3, (uint32_t)isr3, 0x08, 0x8E);
    set_idt_entry(4, (uint32_t)isr4, 0x08, 0x8E);
    set_idt_entry(5, (uint32_t)isr5, 0x08, 0x8E);
    set_idt_entry(6, (uint32_t)isr6, 0x08, 0x8E);
    set_idt_entry(7, (uint32_t)isr7, 0x08, 0x8E);
    set_idt_entry(8, (uint32_t)isr8, 0x08, 0x8E);
    set_idt_entry(9, (uint32_t)isr9, 0x08, 0x8E);
    set_idt_entry(10, (uint32_t)isr10, 0x08, 0x8E);
    set_idt_entry(11, (uint32_t)isr11, 0x08, 0x8E);
    set_idt_entry(12, (uint32_t)isr12, 0x08, 0x8E);
    set_idt_entry(13, (uint32_t)isr13, 0x08, 0x8E);
    set_idt_entry(14, (uint32_t)isr14, 0x08, 0x8E);
    set_idt_entry(15, (uint32_t)isr15, 0x08, 0x8E);
    set_idt_entry(16, (uint32_t)isr16, 0x08, 0x8E);
    set_idt_entry(17, (uint32_t)isr17, 0x08, 0x8E);
    set_idt_entry(18, (uint32_t)isr18, 0x08, 0x8E);
    set_idt_entry(19, (uint32_t)isr19, 0x08, 0x8E);
    set_idt_entry(20, (uint32_t)isr20, 0x08, 0x8E);
    set_idt_entry(21, (uint32_t)isr21, 0x08, 0x8E);
    set_idt_entry(22, (uint32_t)isr22, 0x08, 0x8E);
    set_idt_entry(23, (uint32_t)isr23, 0x08, 0x8E);
    set_idt_entry(24, (uint32_t)isr24, 0x08, 0x8E);
    set_idt_entry(25, (uint32_t)isr25, 0x08, 0x8E);
    set_idt_entry(26, (uint32_t)isr26, 0x08, 0x8E);
    set_idt_entry(27, (uint32_t)isr27, 0x08, 0x8E);
    set_idt_entry(28, (uint32_t)isr28, 0x08, 0x8E);
    set_idt_entry(29, (uint32_t)isr29, 0x08, 0x8E);
    set_idt_entry(30, (uint32_t)isr30, 0x08, 0x8E);
    set_idt_entry(31, (uint32_t)isr31, 0x08, 0x8E);

    // syscalls
    set_idt_entry(128, (uint32_t) isr128, 0x08, 0x8E);
    set_idt_entry(177, (uint32_t) isr177, 0x08, 0x8E);

    set_idt_entry(32, (uint32_t) irq0, 0x08, 0x8E);
    set_idt_entry(32, (uint32_t) irq0, 0x08, 0x8E);
    set_idt_entry(33, (uint32_t) irq1, 0x08, 0x8E);
    set_idt_entry(34, (uint32_t) irq2, 0x08, 0x8E);
    set_idt_entry(35, (uint32_t) irq3, 0x08, 0x8E);
    set_idt_entry(36, (uint32_t) irq4, 0x08, 0x8E);
    set_idt_entry(37, (uint32_t) irq5, 0x08, 0x8E);
    set_idt_entry(38, (uint32_t) irq6, 0x08, 0x8E);
    set_idt_entry(39, (uint32_t) irq7, 0x08, 0x8E);
    set_idt_entry(40, (uint32_t) irq8, 0x08, 0x8E);
    set_idt_entry(41, (uint32_t) irq9, 0x08, 0x8E);
    set_idt_entry(42, (uint32_t) irq10, 0x08, 0x8E);
    set_idt_entry(43, (uint32_t) irq11, 0x08, 0x8E);
    set_idt_entry(44, (uint32_t) irq12, 0x08, 0x8E);
    set_idt_entry(45, (uint32_t) irq13, 0x08, 0x8E);
    set_idt_entry(46, (uint32_t) irq14, 0x08, 0x8E);
    set_idt_entry(47, (uint32_t) irq15, 0x08, 0x8E);
    
    idt_flush((uint32_t) &idtr);
}
