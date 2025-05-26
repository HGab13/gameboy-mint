#ifndef FLAGS_REGISTER_H
#define FLAGS_REGISTER_H

// Function calls

// Convert a flags-register type 8-bit 'f' register
uint8_t flagtof (flagsregister flag);
// Convert an 8-bit 'f' register to a flags-register type
flagsregister ftoflag (uint8_t f);
// Return a flag with the flag_name flag changed to value
uint8_t set_flag (uint8_t old_f, char *flag_name, bool value);


#endif