#include <stdbool.h>
#include <stdint.h>


// TODO: add reference to cpu.c (or, if needed, cpu.h) 
// TODO: add reference to registers.c (or, if needed, registers.h)
// TODO: add reference to flags_register.c (or, if needed, flags_register.h)

/* Various instructions to the CPU 
    
    TODO: ADD (add) - simple instruction that adds specific register's contents to the A register's contents.
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
    L
} ArithmeticTarget;

void execute (cpu *self, Instruction instruction, ArithmeticTarget target);
uint8_t add (cpu *self, uint8_t value);



// TODO: Execute the instructions given to the CPU based on the given instruction and target
void execute (cpu *self, Instruction instruction, ArithmeticTarget target) {
    switch (instruction) {
        case ADD: 
            switch (target) {
                case A:
                    uint8_t value = self.cpu_registers.a;
                    uint8_t new_value = add(value);
                    self.cpu_registers.a = new_value;
                    break;
                case B:
                    uint8_t value = self.cpu_registers.b;
                    uint8_t new_value = add(value);
                    self.cpu_registers.a = new_value;
                    break;
                case C:
                    uint8_t value = self.cpu_registers.c;
                    uint8_t new_value = add(value);
                    self.cpu_registers.a = new_value;
                    break;
                case D:
                    uint8_t value = self.cpu_registers.d;
                    uint8_t new_value = add(value);
                    self.cpu_registers.a = new_value;
                    break;
                case E:
                    uint8_t value = self.cpu_registers.e;
                    uint8_t new_value = add(value);
                    self.cpu_registers.a = new_value;
                    break;
                case H:
                    uint8_t value = self.cpu_registers.h;
                    uint8_t new_value = add(value);
                    self.cpu_registers.a = new_value;
                    break;
                case L:
                    uint8_t value = self.cpu_registers.l;
                    uint8_t new_value = add(value);
                    self.cpu_registers.a = new_value;
                    break;
            }
            break;
        case ADDH:
            break;
        case ADC:
            break;
        case SUB:
            break;
        case SBC:
            break;
        case AND:
            break;
        case OR:
            break;
        case XOR:
            break; 
        case CP:
            break;
        case INC:
            break;
        case DEC:
            break;
        case CCF:
            break;
        case SCF:
            break;
        case RRA:
            break;
        case RLA:
            break;
        case RRCA:
            break;
        case RRLA:
            break;
        case CPL:
            break;
        case BIT:
            break;
        case RESE:
            break;
        case SET:
            break;
        case SRL: 
            break;
        case RR:
            break;
        case RL:
            break;
        case RRC:
            break;
        case RLC:
            break;
        case SRA:
            break;
        case SLA:
            break;
        case SWAP:
            break;
    }
}


// --  Helpers  --

// Simple instruction that adds specific register's contents to the A register's contents.
uint8_t add (cpu *self, uint8_t value) {

    // Add
    uint8_t new_value = self.registers.a + value;
    
    // Determine flags
    bool is_new_value_zero = (new_value == 0);
    bool did_overflow = (new_value < self.cpu_registers.a);
    bool did_half_carry = ((self.cpu_registers.a & 0xF) + (value & 0xF)) > 0xF;


    // Set all the registers to their new values
    self.cpu_registers.f = set_flag(self.cpu_registers.f, "zero", is_new_value_zero);
    self.cpu_registers.f = set_flag(self.cpu_registers.f, "subtract", false);
    self.cpu_registers.f = set_flag(self.cpu_registers.f, "carry", did_overflow);
    // Half Carry is set if adding the lower nibbles of the value and register A
    // together result in a value bigger than 0xF. If the result is larger than 0xF,
    // then the addition caused a carry from the lower nibble to the upper nibble.
    self.cpu_registers.f = set_flag(self.cpu_registers.f, "half_carry", did_half_carry);

    return new_value;
}