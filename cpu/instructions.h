#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include <stdint.h>
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

void execute (cpu *self, Instruction instruction, ArithmeticTarget target, ...);

#endif