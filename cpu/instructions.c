// Standard libraries
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
// Local libraries
#include "cpu.h"
#include "flags-register.h"
#include "instructions-helpers.h"
#include "registers.h"

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
    ADDH,
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
    RESE,
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
	SP
} ArithmeticTarget;

void execute (cpu *self, Instruction instruction, ArithmeticTarget target);


// TODO: Execute the instructions given to the CPU based on the given instruction and target
void execute (cpu *self, Instruction instruction, ArithmeticTarget target) {
    switch (instruction) {
        // ADD (add) - simple instruction that adds specific register's contents to the A register's contents.
        case ADD: 
            switch (target) {
                case A:
                    uint8_t value = self->cpu_registers.a;
                    uint8_t new_value = add(self, value);
                    self->cpu_registers.a = new_value;
                    break;
                case B:
                    uint8_t value = self->cpu_registers.b;
                    uint8_t new_value = add(self, value);
                    self->cpu_registers.a = new_value;
                    break;
                case C:
                    uint8_t value = self->cpu_registers.c;
                    uint8_t new_value = add(self, value);
                    self->cpu_registers.a = new_value;
                    break;
                case D:
                    uint8_t value = self->cpu_registers.d;
                    uint8_t new_value = add(self, value);
                    self->cpu_registers.a = new_value;
                    break;
                case E:
                    uint8_t value = self->cpu_registers.e;
                    uint8_t new_value = add(self, value);
                    self->cpu_registers.a = new_value;
                    break;
                case H:
                    uint8_t value = self->cpu_registers.h;
                    uint8_t new_value = add(self, value);
                    self->cpu_registers.a = new_value;
                    break;
                case L:
                    uint8_t value = self->cpu_registers.l;
                    uint8_t new_value = add(self, value);
                    self->cpu_registers.a = new_value;
                    break;
            }
            break;
        // ADDHL (add to HL) - just like ADD except that the target is added to the HL register
        case ADDHL:
			switch (target) {
				case BC:
					uint16_t value = get_bc(self->cpu_registers);
					uint16_t new_value = add_hl(self, value);

					set_hl(&self->cpu_registers, new_value); // Reminder: &ptr->value means &(ptr->value)
					break;
				case DE:
					uint16_t value = get_de(self->cpu_registers);
					uint16_t new_value = add_hl(self, value);

					set_hl(&self->cpu_registers, new_value); 
					break;
				case HL:
					uint16_t value = get_hl(self->cpu_registers);
					uint16_t new_value = add_hl(self, value);

					set_hl(&self->cpu_registers, new_value); 
					break;
				case SP:
					uint16_t value = cpu->sp;
					uint16_t new_value = add_hl(self, value);

					set_hl(&self->cpu_registers, new_value);
					break;
			}
            break;
        // TODO: ADC (add with carry) - just like ADD except that the value of the carry flag is also added to the number
        case ADC:
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