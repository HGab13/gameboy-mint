// Standard
#include <stdint.h>
// User 
#include "memorybus.h"

// Read byte from 16-bit memory address
// NOTE: FINALLYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYY Once I finish this implementation I hope to fix all the previous things in the instruction implementations
uint8_t read_byte(memorybus self, uint16_t address) {

    uint8_t return_byte = self.memory[address];
    return return_byte;

}