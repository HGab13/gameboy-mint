// Standard libraries
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
// Local libraries
#include "cpu.h"
#include "flags-register.h"
#include "instructions-helpers.h"
#include "registers.h"

#define MAXARGS 1

//TODO: make these enums part of an independent header file, so that other files can use it
// Do so when it's time to implement those other files, so we don't have some weird clutter

/* Various instructions to the CPU 
    
    ADD (add) - simple instruction that adds specific register's contents to the A register's contents.
    ADDHL (add to HL) - just like ADD except that the target is added to the HL register
    ADC (add with carry) - just like ADD except that the value of the carry flag is also added to the number
    SUB (subtract) - subtract the value stored in a specific register with the value in the A register
    SBC (subtract with carry) - just like ADD except that the value of the carry flag is also subtracted from the number
    AND (logical and) - do a bitwise and on the value in a specific register and the value in the A register
    OR (logical or) - do a bitwise or on the value in a specific register and the value in the A register
    XOR (logical xor) - do a bitwise xor on the value in a specific register and the value in the A register
    CP (compare) - just like SUB except the result of the subtraction is not stored back into A
    INC (increment) - increment the value in a specific register by 1
    DEC (decrement) - decrement the value in a specific register by 1
    CCF (complement carry flag) - toggle the value of the carry flag
    SCF (set carry flag) - set the carry flag to true
    RRA (rotate right A register) - bit rotate A register right through the carry flag
    RLA (rotate left A register) - bit rotate A register left through the carry flag
    RRCA (rotate right A register) - bit rotate A register right (not through the carry flag)
    RRLA (rotate left A register) - bit rotate A register left (not through the carry flag)
    CPL (complement) - toggle every bit of the A register
    BIT (bit test) - test to see if a specific bit of a specific register is set
    RESET (bit reset) - set a specific bit of a specific register to 0
    SET (bit set) - set a specific bit of a specific register to 1
    SRL (shift right logical) - bit shift a specific register right by 1
    RR (rotate right) - bit rotate a specific register right by 1 through the carry flag
    RL (rotate left) - bit rotate a specific register left by 1 through the carry flag
    RRC (rorate right) - bit rotate a specific register right by 1 (not through the carry flag)
    RLC (rorate left) - bit rotate a specific register left by 1 (not through the carry flag)
    SRA (shift right arithmetic) - arithmetic shift a specific register right by 1
    SLA (shift left arithmetic) - arithmetic shift a specific register left by 1
    SWAP (swap nibbles) - switch upper and lower nibble of a specific register
*/
typedef enum {
    ADD, 
    ADDHL,
	ADDSP,
    ADC,
    SUB,
    SBC,
    AND, 
    OR,
    XOR, 
    CP,
    INC,
    DEC,
    CCF,
    SCF,
    RRA,
    RLA,
    RRCA,
    RLCA,
    CPL,
    BIT,
    RES,
    SET,
    SRL, 
    RR,
    RL,
    RRC,
    RLC,
    SRA,
    SLA,
    SWAP,
} Instruction;

/* The Register target for the Instruction*/
typedef enum { 
    A,
    B,
    C,
    D,
    E,
    H,
    L,
	AF,
	BC,
	DE,
	HL,
    iHL,
	SP,
	N
} ArithmeticTarget;

//
void execute (cpu *self, Instruction instruction, ArithmeticTarget target, ...);


// TODO: Execute the instructions given to the CPU based on the given instruction and target
void execute (cpu *self, Instruction instruction, ArithmeticTarget target, ...) {

	// Declare our inmediate value
	uint8_t n;

	// Use inmediate value if true, else do not
	if (target == N || instruction == BIT || instruction == RES || instruction == SET) {
		// Initialize our variadic number, a single 8-bit value that can or can not be passed in
		va_list args;
		va_start(args, target);

		// If value exists, place it in a variable. If not, just put it as null and move on.
		// TODO: Apparently there are some instructions that may need this inmediate value to be signed, so I'll need to account for those later on
		n = va_arg(args, int);

		va_end(args);
	} else {
		n = 0;
	}

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
				// ADD n (add inmediate): Adds to the 8-bit A register, the immediate data n, 
				// and stores the result back into the A register.
				case N:
					value_8 = n;
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
        // ADDSP (add to HL) - just like ADD except that the target is added to the SP register and the value is signed
        // via twos' complement
        // TODO: check if this actually works to turn this into a twos' complement or not
		case ADDSP:
			if (target == N) {
				value_8 = ~n + 1; // Twos complement: complement the number and add 1 to it.

				new_value_16 = add_sp(self, value_8); // Change with a new function for the contents of sp
				self->sp = new_value_16;
				break;
			}
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
				// ADC n (adc inmediate): Adds to the 8-bit A register, the immediate data n and the carry flag, 
				// and stores the result back into the A register.
				case N:
					value_8 = n;
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
                case N:
                    value_8 = n;
                    break;
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
                    
                // TODO: SUB (HL): at HL's memory address, SUB
                // TODO: Turns out we need functionality for memory addresses like this.
                // TODO: Once we get to that phase, implement all of these parts
                case iHL:
                    // TODO: Add code for this???
                    value_8 = 0; // No it's not.
                    break;
                // SUB n : SUB inmediate value n
                case N:
                    value_8 = n;
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
                case N:
                    self->cpu_registers.a &= n;
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
                case N:
                    self->cpu_registers.a |= n;
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
                case N:
                    self->cpu_registers.a ^= n;
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
                case N:
                    value_8 = n;
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
            
            if (n >= 0 && n <= 7) {
                bit_test(self, value_8, n);
            } else {
                return 2;
            }

            break;


		// RES (bit reset) - set a specific bit of a specific register to 0
        case RES:
            if (n >= 0 && n <= 7) { 
                switch (target) {
                    case A:
                        value_8 = self->cpu_registers.a;
                        new_value_8 = bit_setting(value_8, n, "RES");
                        
                        self->cpu_registers.a = new_value_8;
                        break;
                    case B:
                        value_8 = self->cpu_registers.b;
                        new_value_8 = bit_setting(value_8, n, "RES");

                        self->cpu_registers.b = new_value_8;
                        break;
                    case C:
                        value_8 = self->cpu_registers.c;
                        new_value_8 = bit_setting(value_8, n, "RES");

                        self->cpu_registers.c = new_value_8;
                        break;
                    case D:
                        value_8 = self->cpu_registers.d;
                        new_value_8 = bit_setting(value_8, n, "RES");

                        self->cpu_registers.d = new_value_8;
                        break;
                    case E:
                        value_8 = self->cpu_registers.e;
                        new_value_8 = bit_setting(value_8, n, "RES");

                        self->cpu_registers.e = new_value_8;
                        break;
                    case H:
                        value_8 = self->cpu_registers.h;
                        new_value_8 = bit_setting(value_8, n, "RES");

                        self->cpu_registers.h = new_value_8;
                        break;
                    case L:
                        value_8 = self->cpu_registers.l;
                        new_value_8 = bit_setting(value_8, n, "RES");

                        self->cpu_registers.l = new_value_8;
                        break;
                    // TODO: YOu know, this repo is currently public and I'm just screaming into these to-dos.
                    // I hope this shows in the future how I get better at programming these things.
                    case iHL:
                        value_8 = 0;
                        new_value_8 = bit_setting(value_8, n, "RES");
                        break;
                }
            } else {
                return 2;
            }
            break;
		// SET (bit set) - set a specific bit of a specific register to 1
        case SET:
            if (n >= 0 && n <= 7) {
                switch (target) {
                    case A:
                        value_8 = self->cpu_registers.a;
                        new_value_8 = bit_setting(value_8, n, "SET");
                        
                        self->cpu_registers.a = new_value_8;
                        break;
                    case B:
                        value_8 = self->cpu_registers.b;
                        new_value_8 = bit_setting(value_8, n, "SET");

                        self->cpu_registers.b = new_value_8;
                        break;
                    case C:
                        value_8 = self->cpu_registers.c;
                        new_value_8 = bit_setting(value_8, n, "SET");

                        self->cpu_registers.c = new_value_8;
                        break;
                    case D:
                        value_8 = self->cpu_registers.d;
                        new_value_8 = bit_setting(value_8, n, "SET");

                        self->cpu_registers.d = new_value_8;
                        break;
                    case E:
                        value_8 = self->cpu_registers.e;
                        new_value_8 = bit_setting(value_8, n, "SET");

                        self->cpu_registers.e = new_value_8;
                        break;
                    case H:
                        value_8 = self->cpu_registers.h;
                        new_value_8 = bit_setting(value_8, n, "SET");

                        self->cpu_registers.h = new_value_8;
                        break;
                    case L:
                        value_8 = self->cpu_registers.l;
                        new_value_8 = bit_setting(value_8, n, "SET");

                        self->cpu_registers.l = new_value_8;
                        break;
                    // TODO: YOu know, this repo is currently public and I'm just screaming into these to-dos.
                    // I hope this shows in the future how I get better at programming these things.
                    case iHL:
                        value_8 = 0;
                        new_value_8 = bit_setting(value_8, n, "SET");
                        break;
                }
            } else {
                return 2;
            }
            break;

		// SRL (shift right logical) - bit shift a specific register right by 1
        case SRL: 
            switch (target) {
                case A:
                    value_8 = self->cpu_registers.a;
                    new_value_8 = shift_rot(self, value_8, "SRL");
                    self->cpu_registers.a = new_value;
                    break;
                case B:
                    value_8 = self->cpu_registers.b;
                    new_value_8 = shift_rot(self, value_8, "SRL");
                    self->cpu_registers.b = new_value;
                    break;
                case C:
                    value_8 = self->cpu_registers.c;
                    new_value_8 = shift_rot(self, value_8, "SRL");
                    self->cpu_registers.c = new_value;
                    break;
                case D:
                    value_8 = self->cpu_registers.d;
                    new_value_8 = shift_rot(self, value_8, "SRL");
                    self->cpu_registers.d = new_value;
                    break;
                case E:
                    value_8 = self->cpu_registers.e;
                    new_value_8 = shift_rot(self, value_8, "SRL");
                    self->cpu_registers.e = new_value;
                    break;
                case H:
                    value_8 = self->cpu_registers.h;
                    new_value_8 = shift_rot(self, value_8, "SRL");
                    self->cpu_registers.h = new_value;
                    break;
                case L:
                    value_8 = self->cpu_registers.l;
                    new_value_8 = shift_rot(self, value_8, "SRL");
                    self->cpu_registers.l = new_value;
                    break;
                case iHL: // TODO: Wwwwhyyyyyyyy I need to find out how to work these 16-bit pointers soonnnnn
                    value_8 = self->cpu_registers.a;
                    new_value_8 = shift_rot(self, value_8, "SRL");
                    self->cpu_registers.a = new_value;
                    break;
            }
            break;
		// RR (rotate right) - bit rotate a specific register right by 1 through the carry flag
        case RR:
            switch (target) {
                case A:
                    value_8 = self->cpu_registers.a;
                    new_value_8 = shift_rot(self, value_8, "RR");
                    self->cpu_registers.a = new_value;
                    break;
                case B:
                    value_8 = self->cpu_registers.b;
                    new_value_8 = shift_rot(self, value_8, "RR");
                    self->cpu_registers.b = new_value;
                    break;
                case C:
                    value_8 = self->cpu_registers.c;
                    new_value_8 = shift_rot(self, value_8, "RR");
                    self->cpu_registers.c = new_value;
                    break;
                case D:
                    value_8 = self->cpu_registers.d;
                    new_value_8 = shift_rot(self, value_8, "RR");
                    self->cpu_registers.d = new_value;
                    break;
                case E:
                    value_8 = self->cpu_registers.e;
                    new_value_8 = shift_rot(self, value_8, "RR");
                    self->cpu_registers.e = new_value;
                    break;
                case H:
                    value_8 = self->cpu_registers.h;
                    new_value_8 = shift_rot(self, value_8, "RR");
                    self->cpu_registers.h = new_value;
                    break;
                case L:
                    value_8 = self->cpu_registers.l;
                    new_value_8 = shift_rot(self, value_8, "RR");
                    self->cpu_registers.l = new_value;
                    break;
                case iHL: // TODO: Wwwwhyyyyyyyy I need to find out how to work these 16-bit pointers soonnnnn
                    value_8 = self->cpu_registers.a;
                    new_value_8 = shift_rot(self, value_8, "RR");
                    self->cpu_registers.a = new_value;
                    break;
            }
            break;
		// RL (rotate left) - bit rotate a specific register left by 1 through the carry flag
        case RL:
            switch (target) {
                case A:
                    value_8 = self->cpu_registers.a;
                    new_value_8 = shift_rot(self, value_8, "RL");
                    self->cpu_registers.a = new_value;
                    break;
                case B:
                    value_8 = self->cpu_registers.b;
                    new_value_8 = shift_rot(self, value_8, "RL");
                    self->cpu_registers.b = new_value;
                    break;
                case C:
                    value_8 = self->cpu_registers.c;
                    new_value_8 = shift_rot(self, value_8, "RL");
                    self->cpu_registers.c = new_value;
                    break;
                case D:
                    value_8 = self->cpu_registers.d;
                    new_value_8 = shift_rot(self, value_8, "RL");
                    self->cpu_registers.d = new_value;
                    break;
                case E:
                    value_8 = self->cpu_registers.e;
                    new_value_8 = shift_rot(self, value_8, "RL");
                    self->cpu_registers.e = new_value;
                    break;
                case H:
                    value_8 = self->cpu_registers.h;
                    new_value_8 = shift_rot(self, value_8, "RL");
                    self->cpu_registers.h = new_value;
                    break;
                case L:
                    value_8 = self->cpu_registers.l;
                    new_value_8 = shift_rot(self, value_8, "RL");
                    self->cpu_registers.l = new_value;
                    break;
                case iHL: // TODO: Wwwwhyyyyyyyy I need to find out how to work these 16-bit pointers soonnnnn
                    value_8 = self->cpu_registers.a;
                    new_value_8 = shift_rot(self, value_8, "RL");
                    self->cpu_registers.a = new_value;
                    break;
            }
            break;
		// RRC (rotate right) - bit rotate a specific register right by 1 (not through the carry flag)
        case RRC:
            switch (target) {
                case A:
                    value_8 = self->cpu_registers.a;
                    new_value_8 = shift_rot(self, value_8, "RRC");
                    self->cpu_registers.a = new_value;
                    break;
                case B:
                    value_8 = self->cpu_registers.b;
                    new_value_8 = shift_rot(self, value_8, "RRC");
                    self->cpu_registers.b = new_value;
                    break;
                case C:
                    value_8 = self->cpu_registers.c;
                    new_value_8 = shift_rot(self, value_8, "RRC");
                    self->cpu_registers.c = new_value;
                    break;
                case D:
                    value_8 = self->cpu_registers.d;
                    new_value_8 = shift_rot(self, value_8, "RRC");
                    self->cpu_registers.d = new_value;
                    break;
                case E:
                    value_8 = self->cpu_registers.e;
                    new_value_8 = shift_rot(self, value_8, "RRC");
                    self->cpu_registers.e = new_value;
                    break;
                case H:
                    value_8 = self->cpu_registers.h;
                    new_value_8 = shift_rot(self, value_8, "RRC");
                    self->cpu_registers.h = new_value;
                    break;
                case L:
                    value_8 = self->cpu_registers.l;
                    new_value_8 = shift_rot(self, value_8, "RRC");
                    self->cpu_registers.l = new_value;
                    break;
                case iHL: // TODO: Wwwwhyyyyyyyy I need to find out how to work these 16-bit pointers soonnnnn
                    value_8 = self->cpu_registers.a;
                    new_value_8 = shift_rot(self, value_8, "RRC");
                    self->cpu_registers.a = new_value;
                    break;
            }
            break;
		// RLC (rotate left) - bit rotate a specific register left by 1 (not through the carry flag)
        case RLC:
            switch (target) {
                case A:
                    value_8 = self->cpu_registers.a;
                    new_value_8 = shift_rot(self, value_8, "RLC");
                    self->cpu_registers.a = new_value;
                    break;
                case B:
                    value_8 = self->cpu_registers.b;
                    new_value_8 = shift_rot(self, value_8, "RLC");
                    self->cpu_registers.b = new_value;
                    break;
                case C:
                    value_8 = self->cpu_registers.c;
                    new_value_8 = shift_rot(self, value_8, "RLC");
                    self->cpu_registers.c = new_value;
                    break;
                case D:
                    value_8 = self->cpu_registers.d;
                    new_value_8 = shift_rot(self, value_8, "RLC");
                    self->cpu_registers.d = new_value;
                    break;
                case E:
                    value_8 = self->cpu_registers.e;
                    new_value_8 = shift_rot(self, value_8, "RLC");
                    self->cpu_registers.e = new_value;
                    break;
                case H:
                    value_8 = self->cpu_registers.h;
                    new_value_8 = shift_rot(self, value_8, "RLC");
                    self->cpu_registers.h = new_value;
                    break;
                case L:
                    value_8 = self->cpu_registers.l;
                    new_value_8 = shift_rot(self, value_8, "RLC");
                    self->cpu_registers.l = new_value;
                    break;
                case iHL: // TODO: Wwwwhyyyyyyyy I need to find out how to work these 16-bit pointers soonnnnn
                    value_8 = self->cpu_registers.a;
                    new_value_8 = shift_rot(self, value_8, "RLC");
                    self->cpu_registers.a = new_value;
                    break;
            }
            break;
		// SRA (shift right arithmetic) - arithmetic shift a specific register right by 1
        case SRA:
            switch (target) {
                case A:
                    value_8 = self->cpu_registers.a;
                    new_value_8 = shift_rot(self, value_8, "SRA");
                    self->cpu_registers.a = new_value;
                    break;
                case B:
                    value_8 = self->cpu_registers.b;
                    new_value_8 = shift_rot(self, value_8, "SRA");
                    self->cpu_registers.b = new_value;
                    break;
                case C:
                    value_8 = self->cpu_registers.c;
                    new_value_8 = shift_rot(self, value_8, "SRA");
                    self->cpu_registers.c = new_value;
                    break;
                case D:
                    value_8 = self->cpu_registers.d;
                    new_value_8 = shift_rot(self, value_8, "SRA");
                    self->cpu_registers.d = new_value;
                    break;
                case E:
                    value_8 = self->cpu_registers.e;
                    new_value_8 = shift_rot(self, value_8, "SRA");
                    self->cpu_registers.e = new_value;
                    break;
                case H:
                    value_8 = self->cpu_registers.h;
                    new_value_8 = shift_rot(self, value_8, "SRA");
                    self->cpu_registers.h = new_value;
                    break;
                case L:
                    value_8 = self->cpu_registers.l;
                    new_value_8 = shift_rot(self, value_8, "SRA");
                    self->cpu_registers.l = new_value;
                    break;
                case iHL: // TODO: Wwwwhyyyyyyyy I need to find out how to work these 16-bit pointers soonnnnn
                    value_8 = self->cpu_registers.a;
                    new_value_8 = shift_rot(self, value_8, "SRA");
                    self->cpu_registers.a = new_value;
                    break;
            }
            break;
		// SLA (shift left arithmetic) - arithmetic shift a specific register left by 1
        case SLA:
            switch (target) {
                case A:
                    value_8 = self->cpu_registers.a;
                    new_value_8 = shift_rot(self, value_8, "SLA");
                    self->cpu_registers.a = new_value;
                    break;
                case B:
                    value_8 = self->cpu_registers.b;
                    new_value_8 = shift_rot(self, value_8, "SLA");
                    self->cpu_registers.b = new_value;
                    break;
                case C:
                    value_8 = self->cpu_registers.c;
                    new_value_8 = shift_rot(self, value_8, "SLA");
                    self->cpu_registers.c = new_value;
                    break;
                case D:
                    value_8 = self->cpu_registers.d;
                    new_value_8 = shift_rot(self, value_8, "SLA");
                    self->cpu_registers.d = new_value;
                    break;
                case E:
                    value_8 = self->cpu_registers.e;
                    new_value_8 = shift_rot(self, value_8, "SLA");
                    self->cpu_registers.e = new_value;
                    break;
                case H:
                    value_8 = self->cpu_registers.h;
                    new_value_8 = shift_rot(self, value_8, "SLA");
                    self->cpu_registers.h = new_value;
                    break;
                case L:
                    value_8 = self->cpu_registers.l;
                    new_value_8 = shift_rot(self, value_8, "SLA");
                    self->cpu_registers.l = new_value;
                    break;
                case iHL: // TODO: Wwwwhyyyyyyyy I need to find out how to work these 16-bit pointers soonnnnn
                    value_8 = self->cpu_registers.a;
                    new_value_8 = shift_rot(self, value_8, "SLA");
                    self->cpu_registers.a = new_value;
                    break;
            }
            break;
		// SWAP (swap nibbles) - switch upper and lower nibble of a specific register
        case SWAP:
            switch (target) {
                case A:
                    swap(self, &self->cpu_registers.a);
                    break;
                case B:
                    swap(self, &self->cpu_registers.b);
                    break;
                case C:
                    swap(self, &self->cpu_registers.c);
                    break;
                case D:
                    swap(self, &self->cpu_registers.d);
                    break;
                case E:
                    swap(self, &self->cpu_registers.e);
                    break;
                case H:
                    swap(self, &self->cpu_registers.h);
                    break;
                case L:
                    swap(self, &self->cpu_registers.l);
                    break;
                case iHL: // TODO: WHYYYY
                    swap(self, &self->cpu_registers.a);
                    break;
            }
            break;
    }
}