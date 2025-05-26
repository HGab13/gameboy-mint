#include <stdint.h>

#include "registers.h"

// -=- DUAL REGISTERS -=-
// -- Combines two registers together for dual-use --

// a & f
uint16_t get_af(registers self) {
    uint16_t af = (((uint16_t) self.a) << 8) | (uint16_t) self.f;
    return af;
}
uint16_t set_af(registers *self, uint16_t value) {
    uint16_t new_a = (value & 0xFF00) >> 8;
    self->a = (uint8_t) new_a;

    uint16_t new_f = value & 0xFF;
    self->f = (uint8_t) new_f;
}
// b & c
uint16_t get_bc(registers self) {
    uint16_t bc = (((uint16_t) self.b) << 8) | (uint16_t) self.c;
    return bc;
}
uint16_t set_bc(registers *self, uint16_t value) {
    uint16_t new_b = (value & 0xFF00) >> 8;
    self->b = (uint8_t) new_b;

    uint16_t new_c = value & 0xFF;
    self->c = (uint8_t) new_c;
}
// d & e
uint16_t get_de(registers self) {
    uint16_t de = (((uint16_t) self.d) << 8) | (uint16_t) self.e;
    return de;
}
uint16_t set_de(registers *self, uint16_t value) {
    uint16_t new_d = (value & 0xFF00) >> 8;
    self->d = (uint8_t) new_d;

    uint16_t new_e = value & 0xFF;
    self->e = (uint8_t) new_e;
}
// h & l
uint16_t get_hl(registers self) {
    uint16_t hl = (((uint16_t) self.h) << 8) | (uint16_t) self.l;
    return hl;
}
uint16_t set_hl(registers *self, uint16_t value) {
    uint16_t new_h = (value & 0xFF00) >> 8;
    self->h = (uint8_t) new_h;

    uint16_t new_l = value & 0xFF;
    self->l = (uint8_t) new_l;
}