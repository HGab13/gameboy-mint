// TODO: Add call to registers.c so we can actually use the registers struct
// {#include "registers.c"} or {#include "registers.h"}, based on if I need header files. Why haven't I checked that yet.
#include <stdint.h>

typedef struct CPU {

  registers cpu_registers;
  uint16_t pc;
  uint16_t sp;
  memorybus bus;

} cpu;