#ifndef INSTRUCTIONS_HELPERS_H
#define INSTRUCTIONS_HELPERS_H

#include "cpu.h"

uint16_t add_hl (cpu *self, uint16_t value);
uint16_t add_sp(cpu *self, uint8_t value);
// Currently supports ADD, ADC, SUB (+ CP), and SBC
uint8_t arthins_a (cpu *self, uint8_t value, char *instruction);
// Combines INC and DEC
uint8_t incdec_8 (cpu *self, uint8_t value, char *instruction);
uint16_t incdec_16 (cpu *self, uint16_t value, char *instruction);
// Combines RRA, RLA, RRCA and RLCA
uint8_t rotate_a(cpu *self, char *instruction);
// Combines SRL, SRA, SLA, RR, RL, RRC, and RLC
uint8_t shift_rot(cpu *self, uint8_t value, char *instruction);

#endif