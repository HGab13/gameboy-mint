// Standard libraries
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
// Local libraries
#include "cpu.h"
#include "flags-register.h"
#include "registers.h"

// --  Helpers  --

// Arithmetic Instruction: Combination for ADD, ADC, SUB (and by extension CP), and SBC
uint8_t arthins_a (cpu *self, uint8_t value, char *instruction) {

    // Declare carry flag
    bool carry = get_flag(self->cpu_registers.f, "carry");

    // Declare subtract flag
    bool subtract = false;

    // Carry out arithmetic
    uint8_t new_value;
    if (strcmp(instruction, "ADD") == 0) {

        new_value = self->cpu_registers.a + value;

    } else if (strcmp(instruction, "ADC") == 0) {

        new_value = self->cpu_registers.a + value + carry;

    } else if (strcmp(instruction, "SUB") == 0) {

        new_value = self->cpu_registers.a - value;
        subtract = true;

    } else if (strcmp(instruction, "SBC") == 0) {

        new_value = self->cpu_registers.a - value - carry;
        subtract = true;

    } else {
        return 0;
    }
    
    // Determine rest of flags
    bool is_new_value_zero = (new_value == 0);
    bool did_overflow = (new_value < self->cpu_registers.a);
    bool did_half_carry = ((self->cpu_registers.a & 0xF) + (value & 0xF)) > 0xF;


    // Set all the registers to their new values
    self->cpu_registers.f = set_flag(self->cpu_registers.f, "zero", is_new_value_zero);
    self->cpu_registers.f = set_flag(self->cpu_registers.f, "subtract", subtract);
    self->cpu_registers.f = set_flag(self->cpu_registers.f, "carry", did_overflow);
    // Half Carry is set if adding the lower nibbles of the value and register A
    // together result in a value bigger than 0xF. If the result is larger than 0xF,
    // then the addition caused a carry from the lower nibble to the upper nibble.
    self->cpu_registers.f = set_flag(self->cpu_registers.f, "half_carry", did_half_carry);

    return new_value;
}

// ADDHL helper function: add to HL
uint16_t add_hl (cpu *self, uint16_t value) {

	// Add 
	uint16_t hl = get_hl(self->cpu_registers);
	uint16_t new_value = hl + value; 

	 // Determine flags
    bool did_overflow = (new_value < hl);
    bool did_half_carry = ((hl & 0xF000) + (value & 0xF000)) > 0xF000; // Overflow is determined from bit 11 to 12


    // Set all the registers to their new values
    //  - Zero left untouched - 
    self->cpu_registers.f = set_flag(self->cpu_registers.f, "subtract", false);
    self->cpu_registers.f = set_flag(self->cpu_registers.f, "carry", did_overflow);
    self->cpu_registers.f = set_flag(self->cpu_registers.f, "half_carry", did_half_carry);

	return new_value;
}

// ADDSP helper: Same as add_hl but with the sp property in the cpu
uint16_t add_sp(cpu *self, uint8_t value) {

    // Add 
	uint16_t sp = self->sp;
	uint16_t new_value = sp + value; 

	 // Determine flags
    bool did_overflow = (new_value < sp);
    bool did_half_carry = ((sp & 0xF000) + (value & 0xF000)) > 0xF000; // Overflow is determined from bit 11 to 12


    // Set all the registers to their new values
    //  - Zero left untouched - 
    self->cpu_registers.f = set_flag(self->cpu_registers.f, "zero", false);
    self->cpu_registers.f = set_flag(self->cpu_registers.f, "subtract", false);
    self->cpu_registers.f = set_flag(self->cpu_registers.f, "carry", did_overflow);
    self->cpu_registers.f = set_flag(self->cpu_registers.f, "half_carry", did_half_carry);

	return new_value;

}

// Increment/Decrease: a combined function for INC and DEC, one for an 8-bit register and another for a 16-bit one
uint8_t incdec_8 (cpu *self, uint8_t value, char *instruction) {

    // Declare the return value
    uint8_t new_value;

    // Determine whether to increment or decrease
    if (strcmp(instruction, "INC") == 0) {

        new_value = value + 1;

    } else if (strcmp(instruction, "DEC") == 0) {

        new_value = value - 1;

    }

    // Set all the flags to their new values
    bool is_new_value_zero = (new_value == 0);
    bool did_half_carry = ((self->cpu_registers.a & 0xF) + (value & 0xF)) > 0xF;

    self->cpu_registers.f = set_flag(self->cpu_registers.f, "zero", is_new_value_zero);
    self->cpu_registers.f = set_flag(self->cpu_registers.f, "subtract", false);
    self->cpu_registers.f = set_flag(self->cpu_registers.f, "half_carry", did_half_carry);
    // - Carry flag left untouched -

    return new_value;

}
uint16_t incdec_16 (cpu *self, uint16_t value, char *instruction) {

    // Declare the return value
    uint16_t new_value;

    // Determine whether to increment or decrease
    if (strcmp(instruction, "INC") == 0) {

        new_value = value + 1;

    } else if (strcmp(instruction, "DEC") == 0) {

        new_value = value - 1;

    }

    // Set all flags to their new values
    // - All flags left untouched -

    return new_value;

}

// Combined function for RRA, RLA, RRCA and RLCA
uint8_t rotate_a(cpu *self, char *instruction) {

    // Declare register A and the residual bit used in the C versions
    uint8_t a_value = self->cpu_registers.a;
    uint8_t a_bit = 0;

    // Declare the return value
    uint8_t new_value;

    // Declare the carry flag for functions that need it
    uint8_t carry_flag = (uint8_t) get_flag(self->cpu_registers.f, "carry");


    // Rotate
    if (strcmp(instruction, "RRA") == 0) {

        new_value = (a_value >> 1) | (carry_flag << 7);

    } else if (strcmp(instruction, "RLA") == 0) {
        
        new_value = (a_value << 1) | carry_flag;

    } else if (strcmp(instruction, "RRCA") == 0) {

        a_bit = a_value & 0xFE; // Retrieve just bit 0
        new_value = (a_value >> 1) | (a_bit << 7);
    
    } else if (strcmp(instruction, "RLCA") == 0) {

        a_bit = (a_value & 0x7F) >> 7; // Retrieve just bit 7
        new_value = (a_value << 1) | a_bit;
        
    } else {
        return 0;
    }

    // Set all flags to their new values
    self->cpu_registers.f = set_flag(self->cpu_registers.f, "zero", false);
    self->cpu_registers.f = set_flag(self->cpu_registers.f, "subtract", false);
    self->cpu_registers.f = set_flag(self->cpu_registers.f, "half_carry", false);

    if (strcmp(instruction, "RRA") == 0 || strcmp(instruction, "RLA") == 0) {

        bool did_overflow = (new_value < a_value);
        self->cpu_registers.f = set_flag(self->cpu_registers.f, "carry", did_overflow);

    }
    else if (strcmp(instruction, "RRCA") == 0 || strcmp(instruction, "RLCA") == 0) {

        self->cpu_registers.f = set_flag(self->cpu_registers.f, "carry", (bool) a_bit);

    }

    return new_value;

}

// Combined function for SRL, SRA, SLA, RR, RL, RRC, and RLC
uint8_t shift_rot(cpu *self, uint8_t value, char *instruction) {

    // Declare the residual bit used in the C versions
    uint8_t bit = 0;

    // Declare the return value
    uint8_t new_value;

    // Declare the carry flag for functions that need it
    uint8_t carry_flag = (uint8_t) get_flag(self->cpu_registers.f, "carry");


    // Execute bit shift or rotation
    if (strcmp(instruction, "SRL") == 0) {

        new_value = value >> 1;

    } else if (strcmp(instruction, "SRA") == 0) {
        
        bit = (value & 0x7F) >> 7; // Retrieve bit 7
        new_value = (value >> 1) | (bit << 7);

    } else if (strcmp(instruction, "SLA") == 0) {

        new_value = value << 1;
        
    } else if (strcmp(instruction, "RR") == 0) {

        new_value = (value >> 1) | (carry_flag << 7);

    } else if (strcmp(instruction, "RL") == 0) {

        new_value = (value << 1) | carry_flag;

    } else if (strcmp(instruction, "RRC") == 0) {

        bit = value & 0xFE; // Retrieve just bit 0
        new_value = (value >> 1) | (bit << 7);
        
    } else if (strcmp(instruction, "RLC") == 0) {
       
        bit = (value & 0x7F) >> 7; // Retrieve just bit 7
        new_value = (value << 1) | bit;

    } else {
        return 0;
    }


    // Set all flags to their new values
    bool is_new_value_zero = (new_value == 0);

    self->cpu_registers.f = set_flag(self->cpu_registers.f, "zero", is_new_value_zero);
    self->cpu_registers.f = set_flag(self->cpu_registers.f, "subtract", false);
    self->cpu_registers.f = set_flag(self->cpu_registers.f, "half_carry", false);

    if (strcmp(instruction, "RR") == 0 || strcmp(instruction, "RL") == 0) {

        bool did_overflow = (new_value < value);
        self->cpu_registers.f = set_flag(self->cpu_registers.f, "carry", did_overflow);

    } else if (strcmp(instruction, "SRL") == 0 || strcmp(instruction, "SRA") == 0 || strcmp(instruction, "SLA") == 0 ||
        strcmp(instruction, "RRC") == 0 || strcmp(instruction, "RLC") == 0) {

        self->cpu_registers.f = set_flag(self->cpu_registers.f, "carry", (bool) bit);

    }


    return new_value;
}