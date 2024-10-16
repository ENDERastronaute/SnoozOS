
#include "headers/keyboard.h"
#include "../low_level/headers/io.h"
#include "../output/headers/screen.h"

void keyboard_interrupt() {
    uint8_t scancode = port_byte_in(0x60);

    print("key pressed");
}
