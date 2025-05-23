#include <stdint.h>

// CPU 8-bit registers
struct Registers {
    uint8_t a;
    uint8_t b;
    uint8_t c;
    uint8_t d;
    uint8_t e;
    uint8_t f;
    uint8_t h;
    uint8_t l;
};

// -- Combines two registers together for dual-use --
uint16_t get_af(struct Registers self);
uint16_t set_af(struct Registers *self, uint16_t value);
uint16_t get_bc(struct Registers self);
uint16_t set_bc(struct Registers *self, uint16_t value);
uint16_t get_de(struct Registers self);
uint16_t set_de(struct Registers *self, uint16_t value);
uint16_t get_hl(struct Registers self);
uint16_t set_hl(struct Registers *self, uint16_t value);



// -=- DUAL REGISTERS -=-
// -- Combines two registers together for dual-use --

// a & f
uint16_t get_af(struct Registers self) {
    uint16_t af = (((uint16_t) self.a) << 8) + (uint16_t) self.f;
    return af;
}
uint16_t set_af(struct Registers *self, uint16_t value) {
    uint16_t new_a = (value >> 8);
    self->a = (uint8_t) new_a;

    uint16_t new_f = (value << 8) >>8 ;
    self->f = (uint8_t) new_f;
}
// b & c
uint16_t get_bc(struct Registers self) {
    uint16_t bc = (((uint16_t) self.b) << 8) + (uint16_t) self.c;
    return bc;
}
uint16_t set_bc(struct Registers *self, uint16_t value) {
    uint16_t new_b = (value >> 8);
    self->b = (uint8_t) new_b;

    uint16_t new_c = (value << 8) >> 8;
    self->c = (uint8_t) new_c;
}
// d & e
uint16_t get_de(struct Registers self) {
    uint16_t de = (((uint16_t) self.d) << 8) + (uint16_t) self.e;
    return de;
}
uint16_t set_de(struct Registers *self, uint16_t value) {
    uint16_t new_d = (value >> 8);
    self->d = (uint8_t) new_d;

    uint16_t new_e = (value << 8) >> 8;
    self->e = (uint8_t) new_e;
}
// h & l
uint16_t get_hl(struct Registers self) {
    uint16_t hl = (((uint16_t) self.h) << 8) + (uint16_t) self.l;
    return hl;
}
uint16_t set_hl(struct Registers *self, uint16_t value) {
    uint16_t new_h = (value >> 8);
    self->h = (uint8_t) new_h;

    uint16_t new_l = (value << 8) >> 8;
    self->l = (uint8_t) new_l;
}