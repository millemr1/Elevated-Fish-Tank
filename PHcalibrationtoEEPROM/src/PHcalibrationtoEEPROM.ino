/*
 * Project PHcalibrationtoEEPROM
 * Description: Store Calibration Factors
 * Author: Micalah Miller
 * Date: 8/23/2022
 */

//for slope

void setup() {


}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  // The core of your code will likely live here.

}

bool floattoEEPROM(float _float1, u_int8_t _startingAddress){  //from least to greatest byte values
  byte 3, 
  byte 2, 
  byte 1, 
  byte 0;

    0 = ((_float1)&& 0xFF); //LSB //maybe make a bool function
    1 = ((_float1 >> 8) && 0XFF);
    2 = ((_float1 >> 16) && 0xFF);
    3 = ((_float1 >> 24)&& 0xFF);  //MSB

    EEPROM.WRITE(_startingAddress, 0);  //storing from least address to greatest
    EEPROM.WRITE(_startingAddress + 1, 1);
    EEPROM.WRITE(_startingAddress + 2, 2);
    EEPROM.WRITE(_startingAddress + 3, 3);

}
 
  