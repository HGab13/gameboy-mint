#ifndef MEMORYBUS_H
#define MEMORYBUS_H

#include <stdint.h>

// Initialize the memory structure, which has 65,536 8-bit chunks of memory.
// When referring to this array, I will call it as if it were the gameboy computer's memory (i.e. indexes will be called addresses).
typedef struct MemoryBus {

    uint8_t memory[0xFFFF];

} memorybus;

uint8_t read_byte(memorybus self, uint16_t address);

#endif