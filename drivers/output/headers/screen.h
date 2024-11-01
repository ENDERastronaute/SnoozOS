//
// Created by ender on 13.10.24.
//

#ifndef SCREEN_H
#define SCREEN_H

#define VIDEO_MEMORY_ADDRESS 0xB8000
#define MAX_ROWS 25
#define MAX_COLS 80

#define WOB 0x0F

#define REG_SCREEN_CTRL 0x3D4
#define REG_SCREEN_DATA 0x3D5
#include "../../low_level/headers/io.h"

void print_char(char character, int col, int row, int attribute);
void print(const char *str, int colour);
void clear_screen();

#endif //SCREEN_H
