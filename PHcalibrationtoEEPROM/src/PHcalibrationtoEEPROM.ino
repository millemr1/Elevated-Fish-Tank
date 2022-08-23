/*
 * Project PHcalibrationtoEEPROM
 * Description: Store Calibration Factors
 * Author: Micalah Miller
 * Date: 8/23/2022
 */


float slope = -88.31;
float offset = 2935.00;
bool s, o;
float slo, off; 

void setup() {
  s = float2eeprom(slope, 0xA1);
  o = float2eeprom(offset, 0xB1);
  Serial.printf("Slope stored %i \n , OffsetStored %i" , s, o);
  slo = eeprom2float(0xA1);
  off = eeprom2float(0XB1);
  Serial.printf("Slope:  %.2f\n , Offset: %.2f\n" , slo , off);
}
void loop() {

  s = float2eeprom(slope, 0xA1);
  o = float2eeprom(offset, 0xB1);
  Serial.printf("Slope stored %i \n , OffsetStored %i" , s, o);
  slo = eeprom2float(0xA1);
  off = eeprom2float(0XB1);
  Serial.printf("Slope:  %.2f\n , Offset: %.2f\n" , slo , off);
}

//maybe make a bool function
bool float2eeprom(float value, uint16_t addr){  //from least to greatest byte values
  byte byte0, byte1, byte2, byte3;
  int32_t value2save;
  bool matched;

  value2save =  value*1000;  //convert to int to cicumvent data type issues

    byte0 = (value2save & 0xFF); //LSB //maybe make a bool function
    byte1 = ((value2save >> 8) & 0XFF);
    byte2 = ((value2save >> 16) & 0xFF);
    byte3 = ((value2save >> 24) & 0xFF);  //MSB

    EEPROM.write(addr, byte0);  //storing from least address to greatest
    EEPROM.write(addr + 1, byte1);
    EEPROM.write(addr + 2, byte2);
    EEPROM.write(addr + 3, byte3);
    if(value = eeprom2float(addr)){ //just == or =
      matched = true;
      Serial.printf("matched \n");
    }
    else{
        matched =  false;
        Serial.printf("not matched \n");
    }
    return matched;
}
float eeprom2float(uint16_t _addr){ 
    byte byte0, byte1, byte2, byte3; //ordered LSB TO MSB
    int value;
    float valueF;

  byte0 = EEPROM.read(_addr);  // values in specfic memory location
  byte1 = EEPROM.read(_addr+1);
  byte2 = EEPROM.read(_addr+2);
  byte3 = EEPROM.read(_addr+3);

  value =  (byte3 << 24) | (byte2 << 16) | (byte1 << 8) | (byte0);
  valueF = value/1000.0;
  Serial.printf("Value %.2f \n " , valueF);
  return valueF;
}