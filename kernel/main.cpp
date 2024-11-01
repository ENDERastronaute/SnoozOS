
#include "../drivers/output/headers/screen.h"
#include "idt/headers/idt.h"

#include <stdint.h>

extern "C" int main() {
    clear_screen();

    print("Loading kernel...\n");

    print("Loading IDT...\n");

    init_IDT();
    install_IRQs();
}
