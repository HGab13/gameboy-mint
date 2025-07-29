#ifndef INSTRUCTIONS_HELPERS_H
#define INSTRUCTIONS_HELPERS_H

#include "cpu-struct.h"

uint16_t add_hl (cpu *self, uint16_t value);
uint16_t add_sp(cpu *self, uint8_t value);
// Currently supports ADD, ADC, SUB (+ CP), and SBC
uint8_t arthins_a (cpu *self, uint8_t value, char *instruction);
// Combines RES and SET
uint8_t bit_setting (uint8_t value, uint8_t bit_number, char *instruction);
// Just BIT
void bit_test (cpu *self, uint8_t value_to_test, uint8_t bit_number);
// Combines INC and DEC
uint8_t incdec_8 (cpu *self, uint8_t value, char *instruction);
uint16_t incdec_16 (cpu *self, uint16_t value, char *instruction);
// Combines RRA, RLA, RRCA and RLCA
uint8_t rotate_a(cpu *self, char *instruction);
// Combines SRL, SRA, SLA, RR, RL, RRC, and RLC
uint8_t shift_rot(cpu *self, uint8_t value, char *instruction);
void swap_nibbles (cpu *self, uint8_t *value)

#endif