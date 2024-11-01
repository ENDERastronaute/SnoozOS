//
// Created by ender on 13.10.24.
//

#include "headers/io.h"

unsigned char port_byte_in(unsigned short port) {
    unsigned char result;
    __asm__("in %%dx, %%al" : "=a" (result) : "d" (port));
    return result;
}

char port_in_b(uint16_t port) {
    char result;
    __asm__ volatile ("inb %1, %0" : "=a" (result) : "dN" (port));
    return result;
}

void port_byte_out(unsigned short port, unsigned char data) {
    __asm__("out %%al, %%dx" : :"a" (data), "d" (port));
}

void port_out_b(uint16_t port, uint8_t value) {
    __asm__ volatile ("outb %1, %0" : : "dN" (port), "a" (value));
}

unsigned short port_word_in(unsigned short port) {
    unsigned short result;
    __asm__("in %%dx, %%ax" : "=a" (result) : "d" (port));

    return result;
}

void port_word_out(unsigned short port, unsigned short data) {
    __asm__("out %%ax, %%dx" : :"a" (data), "d" (port));
}

void memcpy_b(char* src, char* dst, int no_bytes) {
    for (int i = 0; i < no_bytes; i++) {
        *(dst + i) = *(src + i);
    }
}

void memset(void *dst, char val, uint32_t count) {
    char *temp = (char*) dst;

    for (; count != 0; count--) {
        *temp++ = val;
    }
}
