//
// Created by ender on 13.10.24.
//

#include "headers/screen.h"

/**
 * print a string with the desired colour at the desired pos
*/
void print(const char *str, unsigned short color, unsigned int row, unsigned int col) {
  volatile char *video = (volatile char *)0xB8000 + 2 * row * 80 + col;

  while (*str != 0) {
    *video++ = *str++;
    *video++ = color;
  }
}