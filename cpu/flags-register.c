#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "flags-register.h"

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


/* Register f's purposes:
    

    Zero: set to true if the result of the operation is equal to 0.

    Subtract: set to true if the operation was a subtraction.

    Carry: set to true if the operation resulted in an overflow.

    Half Carry: set to true if there is an overflow from the lower nibble (a.k.a the lower four bits) to the upper nibble 
    (a.k.a the upper four bits). Let's take a look at some examples of what this means. In the following diagram, we have the byte 
    143 in binary (0b1000_1111). We then add 0b1 to the number. Notice how the 1 from the lower nibble is carried to the upper 
    nibble. You should already be familiar with carries from elemetry arithmetic. Whenever there's not enough room for a 
    number in a particular digit's place, we carry over to the next digits place.
    
            lower nibble            lower nibble
              ┌--┐                    ┌--┐
          1000 1111  +   1   ==   1001 0000
          └--┘                    └--┘
      upper nibble            upper nibble  
*/

// TODO: find a way to easily type-convert to and from here to flag f in the same way Rust can
// The last four bits of flag f (right to left), which carry the flags
typedef struct FlagsRegister {
    bool zero;
    bool subtract;
    bool half_carry;
    bool carry;
} flagsregister;

// Positions to shift the flags
const uint8_t ZERO_FLAG_BYTE_POSITION = 7;
const uint8_t SUBTRACT_FLAG_BYTE_POSITION = 6;
const uint8_t HALF_CARRY_FLAG_BYTE_POSITION = 5;
const uint8_t CARRY_FLAG_BYTE_POSITION = 4;


// Convert a FlagsRegister type to an 8-bit 'f' register
uint8_t flagtof (flagsregister flag) {
  // Define our f as an unsigned 8-bit integer
  uint8_t new_f = 0;

  // Concatenate all existing flags into the bits of 'f'.
  new_f = ((flag.zero & true) << ZERO_FLAG_BYTE_POSITION) |
    ((flag.subtract & true) << SUBTRACT_FLAG_BYTE_POSITION) |
    ((flag.half_carry & true) << HALF_CARRY_FLAG_BYTE_POSITION) |
    ((flag.carry & true) << CARRY_FLAG_BYTE_POSITION);

  return new_f;

}

// Convert an 8-bit 'f' register to a FlagsRegister type
flagsregister ftoflag (uint8_t f) {

  flagsregister new_flag;

  // If the value at f at the corresponding position is equal to 1, set to true. Else, set it false.
  new_flag.zero = ((f >> ZERO_FLAG_BYTE_POSITION) & 1) != 0;
  new_flag.subtract = ((f >> SUBTRACT_FLAG_BYTE_POSITION) & 1) != 0;
  new_flag.half_carry = ((f >> HALF_CARRY_FLAG_BYTE_POSITION) & 1) != 0;
  new_flag.carry = ((f >> CARRY_FLAG_BYTE_POSITION) & 1) != 0;

  return new_flag;

}

// Give the function a flag name and the value you want it to be, and it'll set it inside the given f flag.
uint8_t set_flag (uint8_t old_f, char *flag_name, bool value) {
  
  // Create a new data structure f
  flagsregister fr;

  // Initialize the new data structure f by reading from flag f's value
  fr = ftoflag(old_f)

  // By way of the flag_name, set the value of the structure f
  if (strcmp(flag_name, "zero") == 0) {
    fr.zero == value;
  }
  else if (strcmp(flag_name, "subtract") == 0) {
    fr.subtract == value;
  }
  else if (strcmp(flag_name, "half_carry") == 0) {
    fr.half_carry == value;
  }
  else if (strcmp(flag_name, "carry") == 0) {
    fr.carry == value;
  }

  // Turn the data structure into the f register
  uint8_t new_f = flagtof(fr)

  // Return the value of this new f register
  return new_f;

}
