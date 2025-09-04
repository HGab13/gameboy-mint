#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include <stdint.h>
#include <stdbool.h>
#include "cpu-struct.h"

/* Various instructions to the CPU 

    TODO: (add remaining instructions)
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

//TODO: Split execute function in two, having the execute function as an intermediary
int execute_mono (cpu *self, Instruction instruction, ArithmeticTarget target);
int execute_n (cpu *self, Instruction instruction, ArithmeticTarget target, uint8_t inmediate_value);



void execute (cpu *self, Instruction instruction, ArithmeticTarget target, bool uses_n, ...);

void execute (cpu *self, Instruction instruction, ArithmeticTarget target, bool uses_n, ...) {

    if (uses_n == true) {

        // Declare inmediate value
        uint8_t n;

        // Initialize our variadic number, a single 8-bit value that can or can not be passed in
		va_list args;
		va_start(args, uses_n);

		// If value exists, place it in a variable. If not, just put it as null and move on.
		// TODO: Apparently there are some instructions that may need this inmediate value to be signed, so I'll need to account for those later on
		n = va_arg(args, int);

		va_end(args);

        execute_n(self, instruction, target, n);
        
    } else {
        execute_mono (self, instruction, target);
    }

}


#endif