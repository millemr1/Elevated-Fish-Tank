# PHASensorAutocal

A Particle project named PHASensorAutocalibration 

## Welcome to the supplamentary code for Autocalibrating the Grove - E-201C-Blue PH sensor!

 
#### ```.ino``` file:
This is additional code used for calibrating the aforementioned PH sensor which otherwise must be calibrated manually. The values would then have to be updated by hard coding them in. This code streamlines that process, and I find it immmenslety useful. Everythign runs in the `setup()` function. The `getOffset()` and `getSlope()` functions take analog readings from the PH sensor and run the proper calibrations needed to get the slope and and offset of this the specific sensor. According to the datasheet for this sensor, the relationship between PH and voltage is linear for this sensor. The functions write the offset and slope values to and EEPROM memory location on the microcontoller that can be pulled accross programs. The header file "SendandPullfromEEPROM.h" allow the float values offset and slope to be updated and sent to the main Fish Tank Code after calibration, if you notice PH readings are not what they ought to be.

See EEPROM TO FlOAT code to understand how the memory locations are working and able to do this accross probrams. 
