
#include "../drivers/output/headers/screen.h"
#include "idt/headers/idt.h"

#include <stdint.h>

int main() {
    clear_screen();

    print("Loading kernel...\n", WOB);

    print("Loading IDT...\n", WOB);

    init_IDT();
    install_IRQs();
}
