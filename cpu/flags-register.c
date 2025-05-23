#include <stdbool.h>
#include <stdint.h>

/* Register f's structure:

       ┌-> Carry
     ┌-+> Subtraction
     | |
    1111 0000
    | |
    └-+> Zero
      └-> Half Carry

    We call this the "flags register," as what it carries is just these four flags

  */

// The last four bits of flag f (right to left), which carry the flags
struct FlagsRegister {
    bool zero;
    bool subtract;
    bool half_carry;
    bool carry;
};

typedef struct FlagsRegister flagsregister;

// Positions to shift the flags
const uint8_t ZERO_FLAG_BYTE_POSITION = 7;
const uint8_t SUBTRACT_FLAG_BYTE_POSITION = 6;
const uint8_t HALF_CARRY_FLAG_BYTE_POSITION = 5;
const uint8_t CARRY_FLAG_BYTE_POSITION = 4;

// Positions to shift the flags under new model
// Fills in the first 4 bytes one by one, and then shifts by four
const uint8_t FLAG_SINGLE_SHIFT_AMOUNT = 1;
const uint8_t FLAG_FULL_SHIFT_AMOUNT = 4;

uint8_t flagtof (flagsregister flag);
flagsregister ftoflag (uint8_t f);


// Convert a FlagsRegister type to an 8-bit 'f' register
uint8_t flagtof (flagsregister flag) {
  // Define our f as an unsigned 8-bit integer
  uint8_t new_f = 0;

  // Set the first four bits to the four flags' values

  new_f += flag.zero & true; // If flag.[flagname] is true, add a 1.
  new_f <<= FLAG_SINGLE_SHIFT_AMOUNT; // Shift by one

  new_f += flag.subtract & true;
  new_f <<= FLAG_SINGLE_SHIFT_AMOUNT;

  new_f += flag.half_carry & true;
  new_f <<= FLAG_SINGLE_SHIFT_AMOUNT;

  new_f += flag.carry & true;
  new_f <<= FLAG_SINGLE_SHIFT_AMOUNT;

  // Shift them back to the last four bits of the 'f' register where they belong
  new_f <<= FLAG_FULL_SHIFT_AMOUNT;

  return new_f;

}

// Convert an 8-bit 'f' register to a FlagsRegister type
/* This is when I found out the bitwise functions' purpose, so this part of the code was NOT affected */
flagsregister ftoflag (uint8_t f) {

  flagsregister new_flag;

  // If the value at f at the corresponding position is equal to 1, set to true. Else, set it false.
  new_flag.zero = ((f << ZERO_FLAG_BYTE_POSITION) & 1) ? true : false;
  new_flag.subtract = ((f << SUBTRACT_FLAG_BYTE_POSITION) & 1) ? true : false;
  new_flag.half_carry = ((f << HALF_CARRY_FLAG_BYTE_POSITION) & 1) ? true : false;
  new_flag.carry = ((f << CARRY_FLAG_BYTE_POSITION) & 1) ? true : false;

  return new_flag;

}
