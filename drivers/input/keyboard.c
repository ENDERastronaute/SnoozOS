
#include "headers/keyboard.h"
#include "../output/headers/screen.h"
#include <stdbool.h>

const char* undercase[128] = {
    0,    0,    "1",  "2",  "3",  "4",  "5",  "6",  // 0-7
    "7",  "8",  "9",  "0",  "'",  "^",  0,    0,    // 8-15
    "q",  "w",  "e",  "r",  "t",  "z",  "u",  "i",  // 16-23
    "o",  "p",  "è",  "$",  0,    0,    "a",  "s",  // 24-31
    "d",  "f",  "g",  "h",  "j",  "k",  "l",  "é",  // 32-39
    "à",  0,    0,    "y",  "x",  "c",  "v",  "b",  // 40-47
    "n",  "m",  ",",  ".",  "-",  0,    "*",  0,    // 48-55
    " ",  0,    0,    0,    0,    0,    0,    0,    // 56-63
    0,    0,    0,    0,    0,    0,    0,    0,    // 64-71
    0,    0,    0,    0,    0,    0,    0,    0,    // 72-79
    0,    0,    0,    0,    0,    0,    0,    0,    // 80-87
    0,    0,    0,    0,    0,    0,    0,    0,    // 88-95
    0,    0,    0,    0,    0,    0,    0,    0,    // 96-103
    0,    0,    0,    0,    0,    0,    0,    0,    // 104-111
    0,    0,    0,    0,    0,    0,    0,    0     // 112-127
};

const char* uppercase[128] = {
    0,    0,    "+",  "\"", "*",  "ç",  "%",  "&",  // 0-7
    "/",  "(",  ")",  "=",  "?",  "`",  0,    0,    // 8-15
    "Q",  "W",  "E",  "R",  "T",  "Z",  "U",  "I",  // 16-23
    "O",  "P",  "ü",  "!",  0,    0,    "A",  "S",  // 24-31
    "D",  "F",  "G",  "H",  "J",  "K",  "L",  "ö",  // 32-39
    "ä",  0,    0,    "Y",  "X",  "C",  "V",  "B",  // 40-47
    "N",  "M",  ";",  ":",  "_",  0,    "*",  0,    // 48-55
    " ",  0,    0,    0,    0,    0,    0,    0,    // 56-63
    0,    0,    0,    0,    0,    0,    0,    0,    // 64-71
    0,    0,    0,    0,    0,    0,    0,    0,    // 72-79
    0,    0,    0,    0,    0,    0,    0,    0,    // 80-87
    0,    0,    0,    0,    0,    0,    0,    0,    // 88-95
    0,    0,    0,    0,    0,    0,    0,    0,    // 96-103
    0,    0,    0,    0,    0,    0,    0,    0,    // 104-111
    0,    0,    0,    0,    0,    0,    0,    0     // 112-127
};

const char* alt_mod[128] = {
    0,    0,    "~",  "ˇ",  "^",  "˘",  "°",  "˛",  // 0-7
    "`",  "˙",  "´",  "˝",  "¨",  "¸",  0,    0,    // 8-15
    "@",  0,    "€",  0,    0,    0,    0,    0,    // 16-23
    0,    0,    "[",  "]",  0,    0,    "{",  "}",  // 24-31
    0,    0,    0,    0,    0,    0,    "\\", 0,    // 32-39
    0,    0,    0,    0,    0,    0,    0,    "|",  // 40-47
    0,    0,    "<",  ">",  0,    0,    0,    0,    // 48-55
    " ",  0,    0,    0,    0,    0,    0,    0,    // 56-63
    0,    0,    0,    0,    0,    0,    0,    0,    // 64-71
    0,    0,    0,    0,    0,    0,    0,    0,    // 72-79
    0,    0,    0,    0,    0,    0,    0,    0,    // 80-87
    0,    0,    0,    0,    0,    0,    0,    0,    // 88-95
    0,    0,    0,    0,    0,    0,    0,    0,    // 96-103
    0,    0,    0,    0,    0,    0,    0,    0,    // 104-111
    0,    0,    0,    0,    0,    0,    0,    0     // 112-127
};

bool caps = false;
bool caps_lock = false;
bool alt = false;

void keyboard_interrupt(struct Interrupt_registers *reg) {
    unsigned char scancode = port_in_b(0x60) & 0X7F;
    unsigned char press = port_in_b(0x60) & 0x80;
    
    switch (scancode) {
        case 0x00:
        case 0xAA:
        case 0xEE:
        case 0xF1:
        case 0xFA:
        case 0xFC:
        case 0xFD:
        case 0xFE:
        case 0xFF:
            print("erreur", WOB);
            break;
        case 0x1: // ESC
        case 0x3B: // F keys
        case 0x3C:
        case 0x3D:
        case 0x3E:
        case 0x3F:
        case 0x40:
        case 0x41:
        case 0x42:
        case 0x43:
        case 0x44:
        case 0x57:
        case 0x58: // end of F keys
            break;
        case 0x2A: // shift
            if (press == 0) {
                caps = true;
            }
            else {
                caps = false;
            }
            break;
        case 0x3A:
            if (press == 0) {
                caps_lock = !caps_lock;
            }
            break;
        case 0xE038:
            if (press == 0) {
                alt = true;
            }
            else {
                alt = false;
            }
            break;
        default:
            if (press == 0 && (caps || caps_lock)) {
                print(uppercase[scancode], WOB);
            }
            else if (press == 0 && alt) {
                print(alt_mod[scancode], WOB);
            }
            else if (press == 0) {
                const char* key = undercase[scancode];

                if (key != 0) {
                    print(key, WOB);
                }
            }
    }
}