#ifndef INSTRUCTIONS_HELPERS_H
#define INSTRUCTIONS_HELPERS_H

#include "cpu.h"

uint8_t add (cpu *self, uint8_t value);
uint16_t add_hl (cpu *self, uint16_t value);

#endif