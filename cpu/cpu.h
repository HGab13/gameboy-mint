#ifndef CPU_H
#define CPU_H

#include <stdint.h>
#include "registers.h"

/* -- CPU -- 
    Contains:
     - The 8 main CPU registers
     - The Program Counter (often abbreviated as PC): tells us which instruction the Game Boy is currently executing. 
       This 16-bit number is capable of addressing of the of 0xFFFF numbers that live in memory. 
       In fact, when we talk about the memory array we don't usually use the term "index", but instead the term "address".
     - SP: stack pointer, "points" to the top of the stack.
     - The memory bus


*/
typedef struct CPU {

  registers cpu_registers;
  uint16_t pc;
  uint16_t sp;
  memorybus bus;

} cpu;

#endif