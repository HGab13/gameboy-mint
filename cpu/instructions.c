// Standard libraries
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
// Local libraries
#include "cpu-struct.h"
#include "flags-register.h"
#include "instructions.h"
#include "instructions-helpers.h"
#include "registers.h"



// !!TODO!!: Assure it compiles ;-;

// TODO: Execute the instructions given to the CPU based on the given instruction and target
int execute_mono (cpu *self, Instruction instruction, ArithmeticTarget target) {

	// Define the value set because apparently scope is weird in c switch statements
	uint8_t value_8;
	uint8_t new_value_8;

	uint16_t value_16;
	uint16_t new_value_16;

    switch (instruction) {
        // ADD (add) - simple instruction that adds specific register's contents to the A register's contents.
        case ADD: 
            switch (target) {
                case A:
                    value_8 = self->cpu_registers.a;
                    break;
                case B:
                    value_8 = self->cpu_registers.b;
                    break;
                case C:
                    value_8 = self->cpu_registers.c;
                    break;
                case D:
                    value_8 = self->cpu_registers.d;
                    break;
                case E:
                    value_8 = self->cpu_registers.e;
                    break;
                case H:
                    value_8 = self->cpu_registers.h;
                    break;
                case L:
                    value_8 = self->cpu_registers.l;
                    break;
				// Add (indirect HL): Add the contents of memory specified by register pair HL to the contents of register A, 
				// and store the results in register A.
				// TODO: Turns out we need functionality for memory addresses like this.
				// TODO: Once we get to that phase, implement all of these parts
				case iHL:
					// TODO: Add code for this???
					value_8 = 0; // No it's not.
					break;
            }

            new_value_8 = arthins_a(self, value_8, "ADD");
			self->cpu_registers.a = new_value_8;

            break;
        // ADDHL (add to HL) - just like ADD except that the target is added to the HL register
        case ADDHL:
			switch (target) {
				case BC:
					value_16 = get_bc(self->cpu_registers);
					break;
				case DE:
					value_16 = get_de(self->cpu_registers);
					break;
				case HL:
					value_16 = get_hl(self->cpu_registers);
					break;
				case SP:
					value_16 = self->sp;
					break;
			}

            new_value_16 = add_hl(self, value_16);
            set_hl(&self->cpu_registers, new_value_16); // Reminder: &ptr->value means &(ptr->value)

            break;

        // ADC (add with carry) - just like ADD except that the value of the carry flag is also added to the number
        case ADC:
            switch (target) {
                case A:
                    value_8 = self->cpu_registers.a;
                    break;
                case B:
                    value_8 = self->cpu_registers.b;
                    break;
                case C:
                    value_8 = self->cpu_registers.c;
                    break;
                case D:
                    value_8 = self->cpu_registers.d;
                    break;
                case E:
                    value_8 = self->cpu_registers.e;
                    break;
                case H:
                    value_8 = self->cpu_registers.h;
                    break;
                case L:
                    value_8 = self->cpu_registers.l;
                    break;
				// Adc (indirect HL):Add the contents of memory specified by register pair HL and carry to the contents of register A, 
				// and store the results in register A.
				// TODO: Turns out we need functionality for memory addresses like this.
				// TODO: Once we get to that phase, implement all of these parts
				case iHL:
					// TODO: Add code for this???
					value_8 = 0; // No it's not.
					break;
            }

            new_value_8 = arthins_a(self, value_8, "ADC");
			self->cpu_registers.a = new_value_8;

            break;
		// SUB (subtract) - subtract the value stored in a specific register with the value in the A register
        case SUB:
            switch (target) {
                case A:
                    value_8 = self->cpu_registers.a;
                    break;
                case B:
                    value_8 = self->cpu_registers.b;
                    break;
                case C:
                    value_8 = self->cpu_registers.c;
                    break;
                case D:
                    value_8 = self->cpu_registers.d;
                    break;
                case E:
                    value_8 = self->cpu_registers.e;
                    break;
                case H:
                    value_8 = self->cpu_registers.h;
                    break;
                case L:
                    value_8 = self->cpu_registers.l;
                    break;
                // TODO: SUB (HL): at HL's memory address, SUB
                // TODO: Turns out we need functionality for memory addresses like this.
                // TODO: Once we get to that phase, implement all of these parts
                case iHL:
                    // TODO: Add code for this???
                    value_8 = 0; // no it's not
                    break;
                // SUB n : SUB inmediate value n
            }

            new_value_8 = arthins_a(self, value_8, "SUB");
            self->cpu_registers.a = new_value_8;

            break;
		// SBC (subtract with carry)-just like ADD except that the value of the carry flag is alsosubtracted from the number
        case SBC:
            switch (target) {
                case A:
                    value_8 = self->cpu_registers.a;
                    break;
                case B:
                    value_8 = self->cpu_registers.b;
                    break;
                case C:
                    value_8 = self->cpu_registers.c;
                    break;
                case D:
                    value_8 = self->cpu_registers.d;
                    break;
                case E:
                    value_8 = self->cpu_registers.e;
                    break;
                case H:
                    value_8 = self->cpu_registers.h;
                    break;
                case L:
                    value_8 = self->cpu_registers.l;
                    break;
                    
                // TODO: SBC (HL): at HL's memory address, SBC
                // TODO: Turns out we need functionality for memory addresses like this.
                // TODO: Once we get to that phase, implement all of these parts
                case iHL:
                    // TODO: Add code for this???
                    value_8 = 0; // No it's not.
                    break;
            }

            new_value_8 = arthins_a(self, value_8, "SBC");
            self->cpu_registers.a = new_value_8;

            break;
		// AND (logical and) - do a bitwise and on the value in a specific register and the value in the A register
        case AND:
            switch (target) {
                case A:
                    self->cpu_registers.a &= self->cpu_registers.a;
                    break;
                case B:
                    self->cpu_registers.a &= self->cpu_registers.b;
                    break;
                case C:
                    self->cpu_registers.a &= self->cpu_registers.c;
                    break;
                case D:
                    self->cpu_registers.a &= self->cpu_registers.d;
                    break;
                case E:
                    self->cpu_registers.a &= self->cpu_registers.e;
                    break;
                case H:
                    self->cpu_registers.a &= self->cpu_registers.h;
                    break;
                case L:
                    self->cpu_registers.a &= self->cpu_registers.l;
                    break;
                case iHL:
                // TODO: figure out HOW TO HANDLE HL POINTERS???????
                    self->cpu_registers.a &= self->cpu_registers.a;
                    break;
            }

            // Evaluate flags
            self->cpu_registers.f = set_flag(self->cpu_registers.f, "zero", (self->cpu_registers.a == 0));
            self->cpu_registers.f = set_flag(self->cpu_registers.f, "subtract", false);
            self->cpu_registers.f = set_flag(self->cpu_registers.f, "half_carry", true);
            self->cpu_registers.f = set_flag(self->cpu_registers.f, "carry", false);

            break;
		// OR (logical or) - do a bitwise or on the value in a specific register and the value in the A register
        case OR:
            switch (target) {
                case A:
                    self->cpu_registers.a |= self->cpu_registers.a;
                    break;
                case B:
                    self->cpu_registers.a |= self->cpu_registers.b;
                    break;
                case C:
                    self->cpu_registers.a |= self->cpu_registers.c;
                    break;
                case D:
                    self->cpu_registers.a |= self->cpu_registers.d;
                    break;
                case E:
                    self->cpu_registers.a |= self->cpu_registers.e;
                    break;
                case H:
                    self->cpu_registers.a |= self->cpu_registers.h;
                    break;
                case L:
                    self->cpu_registers.a |= self->cpu_registers.l;
                    break;
                case iHL:
                // TODO: figure out HOW TO HANDLE HL POINTERS???????
                    self->cpu_registers.a |= self->cpu_registers.a;
                    break;
            }

            // Evaluate flags
            self->cpu_registers.f = set_flag(self->cpu_registers.f, "zero", (self->cpu_registers.a == 0));
            self->cpu_registers.f = set_flag(self->cpu_registers.f, "subtract", false);
            self->cpu_registers.f = set_flag(self->cpu_registers.f, "half_carry", false);
            self->cpu_registers.f = set_flag(self->cpu_registers.f, "carry", false);

            break;
		// XOR (logical xor) - do a bitwise xor on the value in a specific register and the value in the A register
        case XOR:
            switch (target) {
                case A:
                    self->cpu_registers.a ^= self->cpu_registers.a;
                    break;
                case B:
                    self->cpu_registers.a ^= self->cpu_registers.b;
                    break;
                case C:
                    self->cpu_registers.a ^= self->cpu_registers.c;
                    break;
                case D:
                    self->cpu_registers.a ^= self->cpu_registers.d;
                    break;
                case E:
                    self->cpu_registers.a ^= self->cpu_registers.e;
                    break;
                case H:
                    self->cpu_registers.a ^= self->cpu_registers.h;
                    break;
                case L:
                    self->cpu_registers.a ^= self->cpu_registers.l;
                    break;
                case iHL:
                // TODO: figure out HOW TO HANDLE HL POINTERS???????
                    self->cpu_registers.a ^= self->cpu_registers.a;
                    break;
            }

            // Evaluate flags
            self->cpu_registers.f = set_flag(self->cpu_registers.f, "zero", (self->cpu_registers.a == 0));
            self->cpu_registers.f = set_flag(self->cpu_registers.f, "subtract", false);
            self->cpu_registers.f = set_flag(self->cpu_registers.f, "half_carry", false);
            self->cpu_registers.f = set_flag(self->cpu_registers.f, "carry", false);

            break; 
		// CP (compare) - just like SUB except the result of the subtraction is not stored back into A
        case CP:
            switch (target) {
                case A:
                    value_8 = self->cpu_registers.a;
                    break;
                case B:
                    value_8 = self->cpu_registers.b;
                    break;
                case C:
                    value_8 = self->cpu_registers.c;
                    break;
                case D:
                    value_8 = self->cpu_registers.d;
                    break;
                case E:
                    value_8 = self->cpu_registers.e;
                    break;
                case H:
                    value_8 = self->cpu_registers.h;
                    break;
                case L:
                    value_8 = self->cpu_registers.l;
                    break;
                // TODO: Figure out how memory addresses work for this????
                case iHL:
                    value_8 = self->cpu_registers.a;
                    break;
            }
            arthins_a(self, value_8, "SUB");
            break;
		// INC (increment) - increment the value in a specific register by 1
        case INC:
            switch(target) {
                case A:
                    value_8 = self->cpu_registers.a;

                    self->cpu_registers.a = incdec_8(self, value_8, "INC");
                    break;
                case B:
                    value_8 = self->cpu_registers.b;

                    self->cpu_registers.b = incdec_8(self, value_8, "INC");
                    break;
                case C: 
                    value_8 = self->cpu_registers.c;

                    self->cpu_registers.c = incdec_8(self, value_8, "INC");
                    break;
                case D:
                    value_8 = self->cpu_registers.d;

                    self->cpu_registers.d = incdec_8(self, value_8, "INC");
                    break;
                case E: 
                    value_8 = self->cpu_registers.e;

                    self->cpu_registers.e = incdec_8(self, value_8, "INC");
                    break;
                case H:
                    value_8 = self->cpu_registers.h;

                    self->cpu_registers.h = incdec_8(self, value_8, "INC");
                    break;
                    break;
                case L:
                    value_8 = self->cpu_registers.l;

                    self->cpu_registers.l = incdec_8(self, value_8, "INC");
                    break;
                case iHL: // TODO: figure out HL pointer??
                    value_8 = self->cpu_registers.a;
                    break;
                case BC:
                    value_16 = get_bc(self->cpu_registers);

                    set_bc(&self->cpu_registers, incdec_16(self, value_16, "INC"));
                    break;
                case DE:
                    value_16 = get_de(self->cpu_registers);

                    set_de(&self->cpu_registers, incdec_16(self, value_16, "INC"));
                    break;
                case HL:
                    value_16 = get_hl(self->cpu_registers);

                    set_hl(&self->cpu_registers, incdec_16(self, value_16, "INC"));
                    break;
                case SP:
                    value_16 = self->sp;

                    self->sp = incdec_16(self, value_16, "INC");
                    break;
            }
            break;
		// DEC (decrement) - decrement the value in a specific register by 1
        case DEC:
            switch(target) {
                case A:
                    value_8 = self->cpu_registers.a;

                    self->cpu_registers.a = incdec_8(self, value_8, "DEC");
                    break;
                case B:
                    value_8 = self->cpu_registers.b;

                    self->cpu_registers.b = incdec_8(self, value_8, "DEC");
                    break;
                case C: 
                    value_8 = self->cpu_registers.c;

                    self->cpu_registers.c = incdec_8(self, value_8, "DEC");
                    break;
                case D:
                    value_8 = self->cpu_registers.d;

                    self->cpu_registers.d = incdec_8(self, value_8, "DEC");
                    break;
                case E: 
                    value_8 = self->cpu_registers.e;

                    self->cpu_registers.e = incdec_8(self, value_8, "DEC");
                    break;
                case H:
                    value_8 = self->cpu_registers.h;

                    self->cpu_registers.h = incdec_8(self, value_8, "DEC");
                    break;
                    break;
                case L:
                    value_8 = self->cpu_registers.l;

                    self->cpu_registers.l = incdec_8(self, value_8, "DEC");
                    break;
                case iHL: // TODO: figure out HL pointer??
                    value_8 = self->cpu_registers.a;
                    break;
                case BC:
                    value_16 = get_bc(self->cpu_registers);

                    set_bc(&self->cpu_registers, incdec_16(self, value_16, "DEC"));
                    break;
                case DE:
                    value_16 = get_de(self->cpu_registers);

                    set_de(&self->cpu_registers, incdec_16(self, value_16, "DEC"));
                    break;
                case HL:
                    value_16 = get_hl(self->cpu_registers);

                    set_hl(&self->cpu_registers, incdec_16(self, value_16, "DEC"));
                    break;
                case SP:
                    value_16 = self->sp;

                    self->sp = incdec_16(self, value_16, "DEC");
                    break;
            }
            break;


		// CCF (complement carry flag) - toggle the value of the carry flag
        // NOTE: CCF and SCF also set subtract and half-carry's flags to false
        case CCF:
            value_8 = self->cpu_registers.f;
            
            new_value_8 = set_flag(value_8, "carry", ~get_flag(value_8, "carry"));

            self->cpu_registers.f = new_value_8;

            self->cpu_registers.f = set_flag(value_8, "subtract", false);
            self->cpu_registers.f = set_flag(value_8, "half-carry", false);
            break;
		// SCF (set carry flag) - set the carry flag to true
        case SCF:
            value_8 = self->cpu_registers.f;

            new_value_8 = set_flag(value_8, "carry", true);

            self->cpu_registers.f = new_value_8;

            self->cpu_registers.f = set_flag(value_8, "subtract", false);
            self->cpu_registers.f = set_flag(value_8, "half-carry", false);
            break;


		// RRA (rotate right A register) - bit rotate A register right through the carry flag
        // NOTE: "Through the carry flag" means that the contents in the carry flag are copied to the bit left behind
        case RRA:
            rotate_a(self, "RRA");
            break;
		// RLA (rotate left A register) - bit rotate A register left through the carry flag
        case RLA:
            rotate_a(self, "RLA");
            break;
		// RRCA (rotate right A register) - bit rotate A register right (not through the carry flag)
        case RRCA:
            rotate_a(self, "RRCA");
            break;
		// RLCA (rotate left A register) - bit rotate A register left (not through the carry flag)
        case RLCA:
            rotate_a(self, "RLCA");
            break;


		// CPL (complement) - toggle every bit of the A register
        case CPL:
            self->cpu_registers.a = ~self->cpu_registers.a;

            self->cpu_registers.f = set_flag(self->cpu_registers.f, "subtract", true);
            self->cpu_registers.f = set_flag(self->cpu_registers.f, "half_carry", true);
            break;

		// SRL (shift right logical) - bit shift a specific register right by 1
        case SRL: 
            switch (target) {
                case A:
                    value_8 = self->cpu_registers.a;
                    new_value_8 = shift_rot(self, value_8, "SRL");
                    self->cpu_registers.a = new_value_8;
                    break;
                case B:
                    value_8 = self->cpu_registers.b;
                    new_value_8 = shift_rot(self, value_8, "SRL");
                    self->cpu_registers.b = new_value_8;
                    break;
                case C:
                    value_8 = self->cpu_registers.c;
                    new_value_8 = shift_rot(self, value_8, "SRL");
                    self->cpu_registers.c = new_value_8;
                    break;
                case D:
                    value_8 = self->cpu_registers.d;
                    new_value_8 = shift_rot(self, value_8, "SRL");
                    self->cpu_registers.d = new_value_8;
                    break;
                case E:
                    value_8 = self->cpu_registers.e;
                    new_value_8 = shift_rot(self, value_8, "SRL");
                    self->cpu_registers.e = new_value_8;
                    break;
                case H:
                    value_8 = self->cpu_registers.h;
                    new_value_8 = shift_rot(self, value_8, "SRL");
                    self->cpu_registers.h = new_value_8;
                    break;
                case L:
                    value_8 = self->cpu_registers.l;
                    new_value_8 = shift_rot(self, value_8, "SRL");
                    self->cpu_registers.l = new_value_8;
                    break;
                case iHL: // TODO: Wwwwhyyyyyyyy I need to find out how to work these 16-bit pointers soonnnnn
                    value_8 = self->cpu_registers.a;
                    new_value_8 = shift_rot(self, value_8, "SRL");
                    self->cpu_registers.a = new_value_8;
                    break;
            }
            break;
		// RR (rotate right) - bit rotate a specific register right by 1 through the carry flag
        case RR:
            switch (target) {
                case A:
                    value_8 = self->cpu_registers.a;
                    new_value_8 = shift_rot(self, value_8, "RR");
                    self->cpu_registers.a = new_value_8;
                    break;
                case B:
                    value_8 = self->cpu_registers.b;
                    new_value_8 = shift_rot(self, value_8, "RR");
                    self->cpu_registers.b = new_value_8;
                    break;
                case C:
                    value_8 = self->cpu_registers.c;
                    new_value_8 = shift_rot(self, value_8, "RR");
                    self->cpu_registers.c = new_value_8;
                    break;
                case D:
                    value_8 = self->cpu_registers.d;
                    new_value_8 = shift_rot(self, value_8, "RR");
                    self->cpu_registers.d = new_value_8;
                    break;
                case E:
                    value_8 = self->cpu_registers.e;
                    new_value_8 = shift_rot(self, value_8, "RR");
                    self->cpu_registers.e = new_value_8;
                    break;
                case H:
                    value_8 = self->cpu_registers.h;
                    new_value_8 = shift_rot(self, value_8, "RR");
                    self->cpu_registers.h = new_value_8;
                    break;
                case L:
                    value_8 = self->cpu_registers.l;
                    new_value_8 = shift_rot(self, value_8, "RR");
                    self->cpu_registers.l = new_value_8;
                    break;
                case iHL: // TODO: Wwwwhyyyyyyyy I need to find out how to work these 16-bit pointers soonnnnn
                    value_8 = self->cpu_registers.a;
                    new_value_8 = shift_rot(self, value_8, "RR");
                    self->cpu_registers.a = new_value_8;
                    break;
            }
            break;
		// RL (rotate left) - bit rotate a specific register left by 1 through the carry flag
        case RL:
            switch (target) {
                case A:
                    value_8 = self->cpu_registers.a;
                    new_value_8 = shift_rot(self, value_8, "RL");
                    self->cpu_registers.a = new_value_8;
                    break;
                case B:
                    value_8 = self->cpu_registers.b;
                    new_value_8 = shift_rot(self, value_8, "RL");
                    self->cpu_registers.b = new_value_8;
                    break;
                case C:
                    value_8 = self->cpu_registers.c;
                    new_value_8 = shift_rot(self, value_8, "RL");
                    self->cpu_registers.c = new_value_8;
                    break;
                case D:
                    value_8 = self->cpu_registers.d;
                    new_value_8 = shift_rot(self, value_8, "RL");
                    self->cpu_registers.d = new_value_8;
                    break;
                case E:
                    value_8 = self->cpu_registers.e;
                    new_value_8 = shift_rot(self, value_8, "RL");
                    self->cpu_registers.e = new_value_8;
                    break;
                case H:
                    value_8 = self->cpu_registers.h;
                    new_value_8 = shift_rot(self, value_8, "RL");
                    self->cpu_registers.h = new_value_8;
                    break;
                case L:
                    value_8 = self->cpu_registers.l;
                    new_value_8 = shift_rot(self, value_8, "RL");
                    self->cpu_registers.l = new_value_8;
                    break;
                case iHL: // TODO: Wwwwhyyyyyyyy I need to find out how to work these 16-bit pointers soonnnnn
                    value_8 = self->cpu_registers.a;
                    new_value_8 = shift_rot(self, value_8, "RL");
                    self->cpu_registers.a = new_value_8;
                    break;
            }
            break;
		// RRC (rotate right) - bit rotate a specific register right by 1 (not through the carry flag)
        case RRC:
            switch (target) {
                case A:
                    value_8 = self->cpu_registers.a;
                    new_value_8 = shift_rot(self, value_8, "RRC");
                    self->cpu_registers.a = new_value_8;
                    break;
                case B:
                    value_8 = self->cpu_registers.b;
                    new_value_8 = shift_rot(self, value_8, "RRC");
                    self->cpu_registers.b = new_value_8;
                    break;
                case C:
                    value_8 = self->cpu_registers.c;
                    new_value_8 = shift_rot(self, value_8, "RRC");
                    self->cpu_registers.c = new_value_8;
                    break;
                case D:
                    value_8 = self->cpu_registers.d;
                    new_value_8 = shift_rot(self, value_8, "RRC");
                    self->cpu_registers.d = new_value_8;
                    break;
                case E:
                    value_8 = self->cpu_registers.e;
                    new_value_8 = shift_rot(self, value_8, "RRC");
                    self->cpu_registers.e = new_value_8;
                    break;
                case H:
                    value_8 = self->cpu_registers.h;
                    new_value_8 = shift_rot(self, value_8, "RRC");
                    self->cpu_registers.h = new_value_8;
                    break;
                case L:
                    value_8 = self->cpu_registers.l;
                    new_value_8 = shift_rot(self, value_8, "RRC");
                    self->cpu_registers.l = new_value_8;
                    break;
                case iHL: // TODO: Wwwwhyyyyyyyy I need to find out how to work these 16-bit pointers soonnnnn
                    value_8 = self->cpu_registers.a;
                    new_value_8 = shift_rot(self, value_8, "RRC");
                    self->cpu_registers.a = new_value_8;
                    break;
            }
            break;
		// RLC (rotate left) - bit rotate a specific register left by 1 (not through the carry flag)
        case RLC:
            switch (target) {
                case A:
                    value_8 = self->cpu_registers.a;
                    new_value_8 = shift_rot(self, value_8, "RLC");
                    self->cpu_registers.a = new_value_8;
                    break;
                case B:
                    value_8 = self->cpu_registers.b;
                    new_value_8 = shift_rot(self, value_8, "RLC");
                    self->cpu_registers.b = new_value_8;
                    break;
                case C:
                    value_8 = self->cpu_registers.c;
                    new_value_8 = shift_rot(self, value_8, "RLC");
                    self->cpu_registers.c = new_value_8;
                    break;
                case D:
                    value_8 = self->cpu_registers.d;
                    new_value_8 = shift_rot(self, value_8, "RLC");
                    self->cpu_registers.d = new_value_8;
                    break;
                case E:
                    value_8 = self->cpu_registers.e;
                    new_value_8 = shift_rot(self, value_8, "RLC");
                    self->cpu_registers.e = new_value_8;
                    break;
                case H:
                    value_8 = self->cpu_registers.h;
                    new_value_8 = shift_rot(self, value_8, "RLC");
                    self->cpu_registers.h = new_value_8;
                    break;
                case L:
                    value_8 = self->cpu_registers.l;
                    new_value_8 = shift_rot(self, value_8, "RLC");
                    self->cpu_registers.l = new_value_8;
                    break;
                case iHL: // TODO: Wwwwhyyyyyyyy I need to find out how to work these 16-bit pointers soonnnnn
                    value_8 = self->cpu_registers.a;
                    new_value_8 = shift_rot(self, value_8, "RLC");
                    self->cpu_registers.a = new_value_8;
                    break;
            }
            break;
		// SRA (shift right arithmetic) - arithmetic shift a specific register right by 1
        case SRA:
            switch (target) {
                case A:
                    value_8 = self->cpu_registers.a;
                    new_value_8 = shift_rot(self, value_8, "SRA");
                    self->cpu_registers.a = new_value_8;
                    break;
                case B:
                    value_8 = self->cpu_registers.b;
                    new_value_8 = shift_rot(self, value_8, "SRA");
                    self->cpu_registers.b = new_value_8;
                    break;
                case C:
                    value_8 = self->cpu_registers.c;
                    new_value_8 = shift_rot(self, value_8, "SRA");
                    self->cpu_registers.c = new_value_8;
                    break;
                case D:
                    value_8 = self->cpu_registers.d;
                    new_value_8 = shift_rot(self, value_8, "SRA");
                    self->cpu_registers.d = new_value_8;
                    break;
                case E:
                    value_8 = self->cpu_registers.e;
                    new_value_8 = shift_rot(self, value_8, "SRA");
                    self->cpu_registers.e = new_value_8;
                    break;
                case H:
                    value_8 = self->cpu_registers.h;
                    new_value_8 = shift_rot(self, value_8, "SRA");
                    self->cpu_registers.h = new_value_8;
                    break;
                case L:
                    value_8 = self->cpu_registers.l;
                    new_value_8 = shift_rot(self, value_8, "SRA");
                    self->cpu_registers.l = new_value_8;
                    break;
                case iHL: // TODO: Wwwwhyyyyyyyy I need to find out how to work these 16-bit pointers soonnnnn
                    value_8 = self->cpu_registers.a;
                    new_value_8 = shift_rot(self, value_8, "SRA");
                    self->cpu_registers.a = new_value_8;
                    break;
            }
            break;
		// SLA (shift left arithmetic) - arithmetic shift a specific register left by 1
        case SLA:
            switch (target) {
                case A:
                    value_8 = self->cpu_registers.a;
                    new_value_8 = shift_rot(self, value_8, "SLA");
                    self->cpu_registers.a = new_value_8;
                    break;
                case B:
                    value_8 = self->cpu_registers.b;
                    new_value_8 = shift_rot(self, value_8, "SLA");
                    self->cpu_registers.b = new_value_8;
                    break;
                case C:
                    value_8 = self->cpu_registers.c;
                    new_value_8 = shift_rot(self, value_8, "SLA");
                    self->cpu_registers.c = new_value_8;
                    break;
                case D:
                    value_8 = self->cpu_registers.d;
                    new_value_8 = shift_rot(self, value_8, "SLA");
                    self->cpu_registers.d = new_value_8;
                    break;
                case E:
                    value_8 = self->cpu_registers.e;
                    new_value_8 = shift_rot(self, value_8, "SLA");
                    self->cpu_registers.e = new_value_8;
                    break;
                case H:
                    value_8 = self->cpu_registers.h;
                    new_value_8 = shift_rot(self, value_8, "SLA");
                    self->cpu_registers.h = new_value_8;
                    break;
                case L:
                    value_8 = self->cpu_registers.l;
                    new_value_8 = shift_rot(self, value_8, "SLA");
                    self->cpu_registers.l = new_value_8;
                    break;
                case iHL: // TODO: Wwwwhyyyyyyyy I need to find out how to work these 16-bit pointers soonnnnn
                    value_8 = self->cpu_registers.a;
                    new_value_8 = shift_rot(self, value_8, "SLA");
                    self->cpu_registers.a = new_value_8;
                    break;
            }
            break;
		// SWAP (swap nibbles) - switch upper and lower nibble of a specific register
        case SWAP:
            switch (target) {
                case A:
                    swap_nibbles(self, &self->cpu_registers.a);
                    break;
                case B:
                    swap_nibbles(self, &self->cpu_registers.b);
                    break;
                case C:
                    swap_nibbles(self, &self->cpu_registers.c);
                    break;
                case D:
                    swap_nibbles(self, &self->cpu_registers.d);
                    break;
                case E:
                    swap_nibbles(self, &self->cpu_registers.e);
                    break;
                case H:
                    swap_nibbles(self, &self->cpu_registers.h);
                    break;
                case L:
                    swap_nibbles(self, &self->cpu_registers.l);
                    break;
                case iHL: // TODO: WHYYYY
                    swap_nibbles(self, &self->cpu_registers.a);
                    break;
            }
            break;
    }

    return 0;

}

// TODO: Move all functions that needed N values to execute_n
int execute_n (cpu *self, Instruction instruction, ArithmeticTarget target, uint8_t inmediate_value) {

    // Define the value set because apparently scope is weird in c switch statements
	uint8_t value_8;
	uint8_t new_value_8;

	uint16_t value_16;
	uint16_t new_value_16;


    switch(target) {

        // ADD n (add inmediate): Adds to the 8-bit A register, the immediate data n, 
		// and stores the result back into the A register.
        case ADD:
            if (target == N) {
			    value_8 = inmediate_value;

                new_value_8 = arthins_a(self, value_8, "ADD");
                self->cpu_registers.a = new_value_8;
            } else {
                return 2;
            }

            break;

        // ADDSP (add to HL) - just like ADD except that the target is added to the SP register and the value is signed
        // via twos' complement
        // TODO: check if this actually works to turn this into a twos' complement or not
		case ADDSP:
			if (target == N) {
				value_8 = ~inmediate_value + 1; // Twos complement: complement the number and add 1 to it.

				new_value_16 = add_sp(self, value_8); // Change with a new function for the contents of sp
				self->sp = new_value_16;
				break;
			} else {
                return 2;
            }
			break;
        
        // ADC n (adc inmediate): Adds to the 8-bit A register, the immediate data n and the carry flag, 
		// and stores the result back into the A register.
        case ADC:
            if (target == N) {
                value_8 = inmediate_value;

                new_value_8 = arthins_a(self, value_8, "ADC");
                self->cpu_registers.a = new_value_8;
            } else {
                return 2;
            }
        // SUB n : SUB inmediate value n
        case SUB:
            if (target == N) {
                value_8 = inmediate_value;

                new_value_8 = arthins_a(self, value_8, "SUB");
                self->cpu_registers.a = new_value_8;
            } else {
                return 2;
            }

            break;
        // SBC n : SBC inmediate value n
        case SBC:
            if (target == N) {
                value_8 = inmediate_value;

                new_value_8 = arthins_a(self, value_8, "SBC");
                self->cpu_registers.a = new_value_8;
            } else {
                return 2;
            }

            break;
        // AND n: AND inmediate value n
        case AND:
            if (target == N) {
                self->cpu_registers.a &= inmediate_value;

                // Evaluate flags
                self->cpu_registers.f = set_flag(self->cpu_registers.f, "zero", (self->cpu_registers.a == 0));
                self->cpu_registers.f = set_flag(self->cpu_registers.f, "subtract", false);
                self->cpu_registers.f = set_flag(self->cpu_registers.f, "half_carry", true);
                self->cpu_registers.f = set_flag(self->cpu_registers.f, "carry", false);
            } else {
                return 2;
            }

            break;
        // OR n: OR inmediate value n
        case OR:
            if (target == N) {
                self->cpu_registers.a |= inmediate_value;

                // Evaluate flags
                self->cpu_registers.f = set_flag(self->cpu_registers.f, "zero", (self->cpu_registers.a == 0));
                self->cpu_registers.f = set_flag(self->cpu_registers.f, "subtract", false);
                self->cpu_registers.f = set_flag(self->cpu_registers.f, "half_carry", false);
                self->cpu_registers.f = set_flag(self->cpu_registers.f, "carry", false);
            } else {
                return 2;
            }
            break;
        // XOR n: XOR inmediate value n
        case XOR:
            if (target == N) {
                self->cpu_registers.a ^= inmediate_value;
                    
                // Evaluate flags
                self->cpu_registers.f = set_flag(self->cpu_registers.f, "zero", (self->cpu_registers.a == 0));
                self->cpu_registers.f = set_flag(self->cpu_registers.f, "subtract", false);
                self->cpu_registers.f = set_flag(self->cpu_registers.f, "half_carry", false);
                self->cpu_registers.f = set_flag(self->cpu_registers.f, "carry", false);
            } else {
                return 2;
            }
            break; 
        // CP n: CP inmediate value n, which in itself copies SUB
        case CP:
            if (target == N) {
                value_8 = inmediate_value;
                arthins_a(self, value_8, "SUB");
            }
            
            break;








        // BIT (bit test) - test to see if a specific bit of a specific register is set
        case BIT:
            switch (target) {
                case A:
                    value_8 = self->cpu_registers.a;
                    break;
                case B:
                    value_8 = self->cpu_registers.b;
                    break;
                case C:
                    value_8 = self->cpu_registers.c;
                    break;
                case D:
                    value_8 = self->cpu_registers.d;
                    break;
                case E:
                    value_8 = self->cpu_registers.e;
                    break;
                case H:
                    value_8 = self->cpu_registers.h;
                    break;
                case L:
                    value_8 = self->cpu_registers.l;
                    break;
                // TODO: YOu know, this repo is currently public and I'm just screaming into these to-dos.
                // I hope this shows in the future how I get better at programming these things.
                case iHL:
                    value_8 = 0;
                    break;
            }
            
            if (inmediate_value >= 0 && inmediate_value <= 7) {
                bit_test(self, value_8, inmediate_value);
            } else {
                return 2;
            }

            break;


		// RES (bit reset) - set a specific bit of a specific register to 0
        case RES:
            if (inmediate_value >= 0 && inmediate_value <= 7) { 
                switch (target) {
                    case A:
                        value_8 = self->cpu_registers.a;
                        new_value_8 = bit_setting(value_8, inmediate_value, "RES");
                        
                        self->cpu_registers.a = new_value_8;
                        break;
                    case B:
                        value_8 = self->cpu_registers.b;
                        new_value_8 = bit_setting(value_8, inmediate_value, "RES");

                        self->cpu_registers.b = new_value_8;
                        break;
                    case C:
                        value_8 = self->cpu_registers.c;
                        new_value_8 = bit_setting(value_8, inmediate_value, "RES");

                        self->cpu_registers.c = new_value_8;
                        break;
                    case D:
                        value_8 = self->cpu_registers.d;
                        new_value_8 = bit_setting(value_8, inmediate_value, "RES");

                        self->cpu_registers.d = new_value_8;
                        break;
                    case E:
                        value_8 = self->cpu_registers.e;
                        new_value_8 = bit_setting(value_8, inmediate_value, "RES");

                        self->cpu_registers.e = new_value_8;
                        break;
                    case H:
                        value_8 = self->cpu_registers.h;
                        new_value_8 = bit_setting(value_8, inmediate_value, "RES");

                        self->cpu_registers.h = new_value_8;
                        break;
                    case L:
                        value_8 = self->cpu_registers.l;
                        new_value_8 = bit_setting(value_8, inmediate_value, "RES");

                        self->cpu_registers.l = new_value_8;
                        break;
                    // TODO: YOu know, this repo is currently public and I'm just screaming into these to-dos.
                    // I hope this shows in the future how I get better at programming these things.
                    case iHL:
                        value_8 = 0;
                        new_value_8 = bit_setting(value_8, inmediate_value, "RES");
                        break;
                }
            } else {
                return 2;
            }
            break;
		// SET (bit set) - set a specific bit of a specific register to 1
        case SET:
            if (inmediate_value >= 0 && inmediate_value <= 7) {
                switch (target) {
                    case A:
                        value_8 = self->cpu_registers.a;
                        new_value_8 = bit_setting(value_8, inmediate_value, "SET");
                        
                        self->cpu_registers.a = new_value_8;
                        break;
                    case B:
                        value_8 = self->cpu_registers.b;
                        new_value_8 = bit_setting(value_8, inmediate_value, "SET");

                        self->cpu_registers.b = new_value_8;
                        break;
                    case C:
                        value_8 = self->cpu_registers.c;
                        new_value_8 = bit_setting(value_8, inmediate_value, "SET");

                        self->cpu_registers.c = new_value_8;
                        break;
                    case D:
                        value_8 = self->cpu_registers.d;
                        new_value_8 = bit_setting(value_8, inmediate_value, "SET");

                        self->cpu_registers.d = new_value_8;
                        break;
                    case E:
                        value_8 = self->cpu_registers.e;
                        new_value_8 = bit_setting(value_8, inmediate_value, "SET");

                        self->cpu_registers.e = new_value_8;
                        break;
                    case H:
                        value_8 = self->cpu_registers.h;
                        new_value_8 = bit_setting(value_8, inmediate_value, "SET");

                        self->cpu_registers.h = new_value_8;
                        break;
                    case L:
                        value_8 = self->cpu_registers.l;
                        new_value_8 = bit_setting(value_8, inmediate_value, "SET");

                        self->cpu_registers.l = new_value_8;
                        break;
                    // TODO: YOu know, this repo is currently public and I'm just screaming into these to-dos.
                    // I hope this shows in the future how I get better at programming these things.
                    case iHL:
                        value_8 = 0;
                        new_value_8 = bit_setting(value_8, inmediate_value, "SET");
                        break;
                }
            } else {
                return 2;
            }
            break;

    }
    return 0;

}