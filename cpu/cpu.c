// TODO: Figure out if data types can borrow from each other, even if they're from different header files?????
#include <stdint.h>
#include "registers.h"

typedef struct CPU {

  registers cpu_registers;
  uint16_t pc;
  uint16_t sp;
  memorybus bus;

} cpu;