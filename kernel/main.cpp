
#include "../drivers/output/headers/screen.h"
#include "idt/headers/idt.h"

#include <stdint.h>

int main() {
    clear_screen();
    print("Hello World!");
    init_IDT();

    __asm__("sti");

    return 0;
}
