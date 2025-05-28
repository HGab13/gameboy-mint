#ifndef FLAGS_REGISTER_H
#define FLAGS_REGISTER_H

// The last four bits of flag f (right to left), which carry the flags
typedef struct FlagsRegister {
    bool zero;
    bool subtract;
    bool half_carry;
    bool carry;
} flagsregister;

// Function calls

// Convert a flags-register type 8-bit 'f' register
uint8_t flagtof (flagsregister flag);
// Convert an 8-bit 'f' register to a flags-register type
flagsregister ftoflag (uint8_t f);
// Get the specific flag you want from the f register as a bool
bool get_flag(uint8_t old_f, char *flag_name);
// Return a flag with the flag_name flag changed to value
uint8_t set_flag (uint8_t old_f, char *flag_name, bool value);



#endif