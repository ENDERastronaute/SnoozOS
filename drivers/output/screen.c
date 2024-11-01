//
// Created by ender on 13.10.24.
//

#include "headers/screen.h"

void set_cursor(int offset) {
    offset /= 2;
    port_byte_out(REG_SCREEN_CTRL, 0x0F);
    port_byte_out(REG_SCREEN_DATA, (unsigned char) (offset & 0xFF));
    port_byte_out(REG_SCREEN_CTRL, 0x0E);
    port_byte_out(REG_SCREEN_DATA, (unsigned char) ((offset >> 8) & 0xFF));
}

int get_cursor() {
    port_byte_out(REG_SCREEN_CTRL, 14);
    
    int offset = port_byte_in(REG_SCREEN_DATA) << 8;

    port_byte_out(REG_SCREEN_CTRL, 15);

    offset += port_byte_in(REG_SCREEN_DATA);

    return offset*2;
}

int get_screen_offset(int col, int row) {
    return 2 * (row * MAX_COLS + col);
}

int handle_scrolling(int cursor_offset) {
    if (cursor_offset < MAX_COLS * MAX_ROWS * 2) {
        return cursor_offset;
    }

    for (int i = 0; i < MAX_ROWS; i++) {
        memcpy_b((char*) (get_screen_offset(0, i) + VIDEO_MEMORY_ADDRESS),
                 (char*) (get_screen_offset(0, i - 1) + VIDEO_MEMORY_ADDRESS),
                 MAX_COLS * 2);
    }

    char* last_line = (char*) (get_screen_offset(0x0, MAX_ROWS - 1) + VIDEO_MEMORY_ADDRESS);

    for (int i = 0; i < MAX_COLS * 2; i++) {
        last_line[i] = 0;
    }

    cursor_offset -= 2 * MAX_COLS;

    return cursor_offset;
}

void print_char(char character, int col, int row, int attribute) {
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
        offset = get_screen_offset(79, rows);
    }
    else {
        video_memory[offset] = character;
        video_memory[offset + 1] = attribute;
    }

    offset += 2;

    offset = handle_scrolling(offset);

    set_cursor(offset);
}

void print_at(const char *str, int colour, int col, int row) {
    if (col >= 0 && row >= 0) {
        set_cursor(get_screen_offset(col, row));
    }

    int i = 0;

    while (str[i] != 0) {
        print_char(str[i++], col, row, colour);
    }
}

/**
 * print a string with the desired colour at the desired pos
*/
void print(const char *str, int colour) {
  print_at(str, colour, -1, -1);
}

void clear_screen() {
    for (int row = 0; row < MAX_ROWS; row++) {
        for (int col = 0; col < MAX_COLS; col++) {
            print_at(" ", WOB, col, row);
        }
    }

    set_cursor(get_screen_offset(0, 0));
}


