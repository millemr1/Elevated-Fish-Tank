/*
 * Project PHcalibrationtoEEPROM
 * Description: Store Calibration Factors
 * Author: Micalah Miller
 * Date: 8/23/2022
 */


float slope;
float offset;


void setup() {
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  // The core of your code will likely live here.

}
//maybe make a bool function
void floattoEEPROM(float _float1, u_int8_t _startingAddress){  //from least to greatest byte values
  int 0, 1, 2, 3;
  int _0, _1, _2, _3;

    0 = ((_float1)&& 0xFF); //LSB //maybe make a bool function
    1 = ((_float1 >> 8) && 0XFF);
    2 = ((_float1 >> 16) && 0xFF);
    3 = ((_float1 >> 24)&& 0xFF);  //MSB

    EEPROM.WRITE(_startingAddress, 0);  //storing from least address to greatest
    EEPROM.WRITE(_startingAddress + 1, 1);
    EEPROM.WRITE(_startingAddress + 2, 2);
    EEPROM.WRITE(_startingAddress + 3, 3);

  _0 = EEPROM.read(_startingAddress);  // values in specfic memory location
  _1 = EEPROM.read(_startingAddress+1);
  _2 = EEPROM.read(_startingAddress +2);
  _3 = EEPROM.read(_startingAddress +3);


Serial.printf("Address 0: %X \n Address 1: %X \n, Address 2: %X \n Address 3: %X \n", _0, _1, _2, _3);
}
//void EEPROMtoFloat(){}