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
    TODO: ADDHL (add to HL) - just like ADD except that the target is added to the HL register
    TODO: ADC (add with carry) - just like ADD except that the value of the carry flag is also added to the number
    TODO: SUB (subtract) - subtract the value stored in a specific register with the value in the A register
    TODO: SBC (subtract with carry) - just like ADD except that the value of the carry flag is also subtracted from the number
    TODO: AND (logical and) - do a bitwise and on the value in a specific register and the value in the A register
    TODO: OR (logical or) - do a bitwise or on the value in a specific register and the value in the A register
    TODO: XOR (logical xor) - do a bitwise xor on the value in a specific register and the value in the A register
    TODO: CP (compare) - just like SUB except the result of the subtraction is not stored back into A
    TODO: INC (increment) - increment the value in a specific register by 1
    TODO: DEC (decrement) - decrement the value in a specific register by 1
    TODO: CCF (complement carry flag) - toggle the value of the carry flag
    TODO: SCF (set carry flag) - set the carry flag to true
    TODO: RRA (rotate right A register) - bit rotate A register right through the carry flag
    TODO: RLA (rotate left A register) - bit rotate A register left through the carry flag
    TODO: RRCA (rotate right A register) - bit rotate A register right (not through the carry flag)
    TODO: RRLA (rotate left A register) - bit rotate A register left (not through the carry flag)
    TODO: CPL (complement) - toggle every bit of the A register
    TODO: BIT (bit test) - test to see if a specific bit of a specific register is set
    TODO: RESET (bit reset) - set a specific bit of a specific register to 0
    TODO: SET (bit set) - set a specific bit of a specific register to 1
    TODO: SRL (shift right logical) - bit shift a specific register right by 1
    TODO: RR (rotate right) - bit rotate a specific register right by 1 through the carry flag
    TODO: RL (rotate left) - bit rotate a specific register left by 1 through the carry flag
    TODO: RRC (rorate right) - bit rotate a specific register right by 1 (not through the carry flag)
    TODO: RLC (rorate left) - bit rotate a specific register left by 1 (not through the carry flag)
    TODO: SRA (shift right arithmetic) - arithmetic shift a specific register right by 1
    TODO: SLA (shift left arithmetic) - arithmetic shift a specific register left by 1
    TODO: SWAP (swap nibbles) - switch upper and lower nibble of a specific register
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
    RRLA,
    CPL,
    BIT,
    RESET,
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
	if (target == N) {
		// Initialize our variadic number, a single 8-bit value that can or can not be passed in
		va_list args;
		va_start(args, target);

		// If value exists, place it in a variable. If not, just put it as null and move on.
		// TODO: Apparently there are some values in here that may be signed???
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
                    new_value_8 = add(self, value_8);
                    self->cpu_registers.a = new_value_8;
                    break;
                case B:
                    value_8 = self->cpu_registers.b;
                    new_value_8 = add(self, value_8);
                    self->cpu_registers.a = new_value_8;
                    break;
                case C:
                    value_8 = self->cpu_registers.c;
                    new_value_8 = add(self, value_8);
                    self->cpu_registers.a = new_value_8;
                    break;
                case D:
                    value_8 = self->cpu_registers.d;
                    new_value_8 = add(self, value_8);
                    self->cpu_registers.a = new_value_8;
                    break;
                case E:
                    value_8 = self->cpu_registers.e;
                    new_value_8 = add(self, value_8);
                    self->cpu_registers.a = new_value_8;
                    break;
                case H:
                    value_8 = self->cpu_registers.h;
                    new_value_8 = add(self, value_8);
                    self->cpu_registers.a = new_value_8;
                    break;
                case L:
                    value_8 = self->cpu_registers.l;
                    new_value_8 = add(self, value_8);
                    self->cpu_registers.a = new_value_8;
                    break;
				// Add (indirect HL): Add the contents of memory specified by register pair HL to the contents of register A, 
				// and store the results in register A.
				// TODO: Turns out we need functionality for memory addresses like this.
				// TODO: Once we get to that phase, implement all of these parts
				case HL:
					// TODO: Add code for this???
					value_8 = 0; // No it's not.

					new_value_8 = add(self, value_8);
					self->cpu_registers.a = new_value_8;
					break;
				// ADD n (add inmediate): Adds to the 8-bit A register, the immediate data n, 
				// and stores the result back into the A register.
				case N:
					value_8 = n;

					new_value_8 = add(self, value_8);
					self->cpu_registers.a = new_value_8;
					break;
            }
            break;
        // ADDHL (add to HL) - just like ADD except that the target is added to the HL register
        case ADDHL:
			switch (target) {
				case BC:
					value_16 = get_bc(self->cpu_registers);
					new_value_16 = add_hl(self, value_16);

					set_hl(&self->cpu_registers, new_value_16); // Reminder: &ptr->value means &(ptr->value)
					break;
				case DE:
					value_16 = get_de(self->cpu_registers);
					new_value_16 = add_hl(self, value_16);

					set_hl(&self->cpu_registers, new_value_16); 
					break;
				case HL:
					value_16 = get_hl(self->cpu_registers);
					new_value_16 = add_hl(self, value_16);

					set_hl(&self->cpu_registers, new_value_16); 
					break;
				case SP:
					value_16 = self->sp;
					new_value_16 = add_hl(self, value_16);

					set_hl(&self->cpu_registers, new_value_16);
					break;
			}
            break;
		case ADDSP:
			if (target == N) {
				value_8 = ~n + 1; // Twos complement: complement the number and add 1 to it.

				new_value_16 = add_sp(self, value_8); // Change with a new function for the contents of sp
				self->sp = new_value_16;
				break;
			}
			break;
        // TODO: ADC (add with carry) - just like ADD except that the value of the carry flag is also added to the number
        case ADC:
            switch (target) {
                case A:
                    value_8 = self->cpu_registers.a;
                    new_value_8 = add_c(self, value_8);
                    self->cpu_registers.a = new_value_8;
                    break;
                case B:
                    value_8 = self->cpu_registers.b;
                    new_value_8 = add_c(self, value_8);
                    self->cpu_registers.a = new_value_8;
                    break;
                case C:
                    value_8 = self->cpu_registers.c;
                    new_value_8 = add_c(self, value_8);
                    self->cpu_registers.a = new_value_8;
                    break;
                case D:
                    value_8 = self->cpu_registers.d;
                    new_value_8 = add_c(self, value_8);
                    self->cpu_registers.a = new_value_8;
                    break;
                case E:
                    value_8 = self->cpu_registers.e;
                    new_value_8 = add_c(self, value_8);
                    self->cpu_registers.a = new_value_8;
                    break;
                case H:
                    value_8 = self->cpu_registers.h;
                    new_value_8 = add_c(self, value_8);
                    self->cpu_registers.a = new_value_8;
                    break;
                case L:
                    value_8 = self->cpu_registers.l;
                    new_value_8 = add_c(self, value_8);
                    self->cpu_registers.a = new_value_8;
                    break;
				// Add (indirect HL): Add the contents of memory specified by register pair HL to the contents of register A, 
				// and store the results in register A.
				// TODO: Turns out we need functionality for memory addresses like this.
				// TODO: Once we get to that phase, implement all of these parts
				case HL:
					// TODO: Add code for this???
					value_8 = 0; // No it's not.

					new_value_8 = add(self, value_8);
					self->cpu_registers.a = new_value_8;
					break;
				// ADD n (add inmediate): Adds to the 8-bit A register, the immediate data n, 
				// and stores the result back into the A register.
				case N:
					value_8 = n;

					new_value_8 = add_c(self, value_8);
					self->cpu_registers.a = new_value_8;
					break;
            }
            break;
		// TODO: SUB (subtract) - subtract the value stored in a specific register with the value in the A register
        case SUB:
            break;
		//TODO: SBC (subtract with carry)-just like ADD except that the value of the carry flag is alsosubtracted from the number
        case SBC:
            break;
		// TODO: AND (logical and) - do a bitwise and on the value in a specific register and the value in the A register
        case AND:
            break;
		// TODO: OR (logical or) - do a bitwise or on the value in a specific register and the value in the A register
        case OR:
            break;
		// TODO: XOR (logical xor) - do a bitwise xor on the value in a specific register and the value in the A register
        case XOR:
            break; 
		// TODO: CP (compare) - just like SUB except the result of the subtraction is not stored back into A
        case CP:
            break;
		// TODO: INC (increment) - increment the value in a specific register by 1
        case INC:
            break;
		// TODO: DEC (decrement) - decrement the value in a specific register by 1
        case DEC:
            break;
		// TODO: CCF (complement carry flag) - toggle the value of the carry flag
        case CCF:
            break;
		// TODO: SCF (set carry flag) - set the carry flag to true
        case SCF:
            break;
		// TODO: RRA (rotate right A register) - bit rotate A register right through the carry flag
        case RRA:
            break;
		// TODO: RLA (rotate left A register) - bit rotate A register left through the carry flag
        case RLA:
            break;
		// TODO: RRCA (rotate right A register) - bit rotate A register right (not through the carry flag)
        case RRCA:
            break;
		// TODO: RRLA (rotate left A register) - bit rotate A register left (not through the carry flag)
        case RRLA:
            break;
		// TODO: CPL (complement) - toggle every bit of the A register
        case CPL:
            break;
		// TODO: BIT (bit test) - test to see if a specific bit of a specific register is set
        case BIT:
            break;
		// TODO: RESET (bit reset) - set a specific bit of a specific register to 0
        case RESET:
            break;
		// TODO: SET (bit set) - set a specific bit of a specific register to 1
        case SET:
            break;
		// TODO: SRL (shift right logical) - bit shift a specific register right by 1
        case SRL: 
            break;
		// TODO: RR (rotate right) - bit rotate a specific register right by 1 through the carry flag
        case RR:
            break;
		// TODO: RL (rotate left) - bit rotate a specific register left by 1 through the carry flag
        case RL:
            break;
		// TODO: RRC (rorate right) - bit rotate a specific register right by 1 (not through the carry flag)
        case RRC:
            break;
		// TODO: RLC (rorate left) - bit rotate a specific register left by 1 (not through the carry flag)
        case RLC:
            break;
		// TODO: SRA (shift right arithmetic) - arithmetic shift a specific register right by 1
        case SRA:
            break;
		// TODO: SLA (shift left arithmetic) - arithmetic shift a specific register left by 1
        case SLA:
            break;
		// TODO: SWAP (swap nibbles) - switch upper and lower nibble of a specific register
        case SWAP:
            break;
    }
}