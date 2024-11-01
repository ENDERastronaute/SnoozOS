
#ifndef IDT_H
#define IDT_H

#include "../../../drivers/low_level/headers/io.h"

void init_IDT();
void install_IRQs();

#endif // !IDT_H
