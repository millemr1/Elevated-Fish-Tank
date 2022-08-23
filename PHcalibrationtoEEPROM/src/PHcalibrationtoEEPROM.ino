/*
 * Project PHcalibrationtoEEPROM
 * Description: Store Calibration Factors
 * Author: Micalah Miller
 * Date: 8/23/2022
 */


float slope = -88.31;
float offset = 2935.00;
bool s, o;
int store; 


void setup() {
  s = floattoEEPROM(slope, 0xA1);
  o = floattoEEPROM(offset, 0xB1);
  Serial.printf('Slope stored %i \n , OffsetStored');
  

}
// void loop() {

// }
//maybe make a bool function
bool float2eeprom(float value, u_int16_t addr){  //from least to greatest byte values
 
  int byte0, byte1, byte2, byte3;
  
  int value2save;
  bool matched;

  value2save =  value*1000

    byte0 = (value2save & 0xFF); //LSB //maybe make a bool function
    byte1 = ((value2save >> 8) & 0XFF);
    byte2 = ((value2save >> 16) & 0xFF);
    byte3 = ((value2save >> 24) & 0xFF);  //MSB

    EEPROM.write(addr, byte_0);  //storing from least address to greatest
    EEPROM.write(addr + 1, byte_1);
    EEPROM.write(addr + 2, byte_2);
    EEPROM.write(addr + 3, byte_3);
    if(value = eeprom2float(addr)){ //just == or =
      matched = true;
      Serial.printf("matched \n");
    }
    else{
        matched =  false;
        Serial.printf("not matched \n");
    }
}
float eeprom2float(u_int16_t _addr){ 
    int byte0, byte1, byte2, byte3; //ordered LSB TO MSB
    int value;
    float valueF;

  byte0 = EEPROM.read(addr);  // values in specfic memory location
  byte1 = EEPROM.read(_startingAddress+1);
  byte2 = EEPROM.read(_startingAddress+2);
  byte3 = EEPROM.read(_startingAddress+3);

  value =  (byte3 << 24) | (byte2 << 16) | (byte1 << 8) | (byte0);
  valueF = value/1000.0
  Serial.printf("Value %.2f \n " , value);
  return valueF;
}

