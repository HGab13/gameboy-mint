#ifndef CPU_H
#define CPU_H

#include <stdint.h>
#include "cpu-struct.h"

// The cpu's commands for every step in the program counter
void step (cpu *self);


#endif