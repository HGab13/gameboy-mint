#include <stdint.h>

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

uint16_t get_bc(struct Registers self);
uint16_t set_bc(struct Registers *self, uint16_t value);

// Combines the b and c registers for a single read or write
uint16_t get_bc(struct Registers self) {
    uint16_t bc = ((uint16_t) self.b) << 8 | (uint16_t) self.c;
    return bc;
}
uint16_t set_bc(struct Registers *self, uint16_t value) {
    uint16_t new_b = ((value & 0xFF00) >> 8);
    self->b = (uint8_t) new_b;

    uint16_t new_c = (value & 0xFF);
    self->c = (uint8_t) new_c;
}