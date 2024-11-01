//
// Created by ender on 13.10.24.
//

#ifndef LOW_H
#define LOW_H

#include "stdint.h"

struct Interrupt_registers {
    uint32_t cr2;
    uint32_t ds;
    uint32_t edi;
    uint32_t esi;
    uint32_t ebp;
    uint32_t esp;
    uint32_t ebx;
    uint32_t edx;
    uint32_t ecx;
    uint32_t eax;
    uint32_t vector;
    uint32_t err_code;
    uint32_t eip;
    uint32_t csm; 
    uint32_t eflags;
    uint32_t useresp;
    uint32_t ss;
};

unsigned char port_byte_in(unsigned short port);
char port_in_b(uint16_t port);

void port_byte_out(unsigned short port, unsigned char data);
void port_out_b(uint16_t port, uint8_t value);

void memcpy_b(char* src, char* dst, int no_bytes);
void memset(void* dst, char val, uint32_t count);

#endif //LOW_H
