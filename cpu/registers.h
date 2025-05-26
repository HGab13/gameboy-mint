#ifndef REGISTERS_H
#define REGISTERS_H

// CPU 8-bit registers
typedef struct Registers {
    uint8_t a;
    uint8_t b;
    uint8_t c;
    uint8_t d;
    uint8_t e;
    uint8_t f;
    uint8_t h;
    uint8_t l;
} registers;

// -- Function declarations: Combines two registers together for dual-use --
uint16_t get_af(registers self);
uint16_t set_af(registers *self, uint16_t value);
uint16_t get_bc(registers self);
uint16_t set_bc(registers *self, uint16_t value);
uint16_t get_de(registers self);
uint16_t set_de(registers *self, uint16_t value);
uint16_t get_hl(registers self);
uint16_t set_hl(registers *self, uint16_t value);

#endif