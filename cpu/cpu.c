#include <stdint.h>
#include "cpu.h"
#include "memorybus.h"



void step (cpu *self) {

    // The byte that'll be used for our instruction set
    uint8_t instruction_byte = read_byte(self->bus, self->pc);

    // Declare the next step in the program counter
    uint16_t next_pc;
    if (1 == 1) {

        execute();

    } else {
        // Unkown instruction found for: 0x%X
        printf("Uh oh! Dingus got into an invalid memory address!!!! \n No instructions were found at your 0x%X", instruction_byte); 
        // TODO: find a way to panic/abort without causting memory leakage
        abort();
    }

    self->pc = next_pc;

}
