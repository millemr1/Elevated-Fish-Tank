# PHcalibrationtoEEPROM

A Particle project named PHcalibrationtoEEPROM

## Welcome to your project!

#### ```.ino``` file:
This code engages the Electrically Erasable Programable Read-Only Memory addresses on the microcontroller to store and locate a 4-byte floating point value on the microcontoller. The `eeprom2float()` converts bytes of memory from LSB TO MSB sent to the an memory locations passed into it and converts it back into its complete floating point form. The `float2eerprom` works from MSB to LSB using bitshifting to get the value to the memory addresses in an apporpiate order. 
