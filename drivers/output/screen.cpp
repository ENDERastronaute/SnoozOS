//
// Created by ender on 13.10.24.
//

#include "headers/screen.h"

int get_screen_offset(int offset) {
    port_byte_out(REG_SCREEN_CTRL, 14);
    port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset >> 8));
    port_byte_out(REG_SCREEN_CTRL, 15)

    return 0;
}

void print_char(char character, int col, int row, char attribute) {
    volatile unsigned char *video_memory = (volatile unsigned char *) VIDEO_MEMORY_ADDRESS;

    int offset;

    if (col >= 0 && row >= 0) {
        offset = get_screen_offset(col, row);
    }
    else {
        offset = get_cursor();
    }

    if (character == '\n') {
        int rows = offset / (2 * MAX_COLS);
    }
    else {
        video_memory[offset] = character;
        video_memory[offset + 1] = attribute;
    }

    offset += 2;

    offset = handle_scrolling(offset);

    set_cursor(offset);
}

/**
 * print a string with the desired colour at the desired pos
*/
void print(const char *str, unsigned short color, unsigned int row, unsigned int col) {
  volatile char *video_memory = (volatile char *) VIDEO_MEMORY_ADDRESS + 2 * row * 80 + col;

  while (*str != 0) {
    *video_memory++ = *str++;
    *video_memory++ = color;
  }
}
