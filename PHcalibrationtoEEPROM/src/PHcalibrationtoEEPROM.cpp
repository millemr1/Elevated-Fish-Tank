/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "/Users/Layla2/Documents/IoT/Elevated-Fish-Tank/PHcalibrationtoEEPROM/src/PHcalibrationtoEEPROM.ino"
/*
 * Project PHcalibrationtoEEPROM
 * Description: Store Calibration Factors
 * Author: Micalah Miller
 * Date: 8/23/2022
 */


void setup();
void floattoEEPROM(double _float1, u_int8_t _startingAddress);
#line 9 "/Users/Layla2/Documents/IoT/Elevated-Fish-Tank/PHcalibrationtoEEPROM/src/PHcalibrationtoEEPROM.ino"
double slope = -88.31;
double offset = 2935.00;

void setup() {
  floattoEEPROM(slope, 0xA1);
  floattoEEPROM(offset, 0xB1);
}

// void loop() {

// }
//maybe make a bool function
void floattoEEPROM(double _float1, u_int8_t _startingAddress){  //from least to greatest byte values
  int byte_0, byte_1, byte_2, byte_3;
  int _0, _1, _2, _3;

    byte_0 = (_float1 && 0xFF); //LSB //maybe make a bool function
    byte_1 = ((_float1 >> 8) && 0XFF);
    byte_2 = ((_float1 >> 16) && 0xFF);
    byte_3 = ((_float1 >> 24)&& 0xFF);  //MSB

    EEPROM.write(_startingAddress, byte_0);  //storing from least address to greatest
    EEPROM.write(_startingAddress + 1, byte_1);
    EEPROM.write(_startingAddress + 2, byte_2);
    EEPROM.write(_startingAddress + 3, byte_3);

  _0 = EEPROM.read(_startingAddress);  // values in specfic memory location
  _1 = EEPROM.read(_startingAddress+1);
  _2 = EEPROM.read(_startingAddress+2);
  _3 = EEPROM.read(_startingAddress+3);

Serial.printf("Address 0: %X \n Address 1: %X \n, Address 2: %X \n Address 3: %X \n", _0, _1, _2, _3);
}
//void EEPROMtoFloat(){}