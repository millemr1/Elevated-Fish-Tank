/*
 * Project PHASensorAutocal
 * Description: AutoCalibrate the PH sensor
 * Author: Micalah Miller
 * Date: 08/24/2022
 */

#include "float2eepromandBack.h"

int phPin = A4;
float phHigh = 10.00;  //values can be changed bases on the ph values one has handy 
float phLow =  4.00;
float voltageHigh, voltageLow;
float s, o;

void setup() {  //do I want to run once of in void loop
  Serial.begin(9600);
  pinMode(phPin, INPUT);
  Serial.printf("Put in high PH \n");
  delay(30000);
  voltageHigh = getRawVoltage(phPin);  //take a moment to autocalibrate this?
  Serial.printf("Voltage for high PH is: %.2f \n", voltageHigh);
  delay(1000);

  Serial.printf("Move to a lower PH");

  delay(60000);  //time to move between sesnors 10 jars

  voltageLow = getRawVoltage(phPin);
  Serial.printf("Voltage for Low PH is: %.2f \n", voltageLow);
  delay(1000);

  Serial.printf("Calibrating \n");
  s = getSlope(voltageLow, voltageHigh, phLow, phHigh);

  Serial.printf("slope PH is: %.2f \n", s);
  o = getOffset(voltageHigh, phHigh, s);  
  Serial.printf("offset is %.2f \n" , o);

}


float getRawVoltage(int _sensorPin){
  int reading, i;
  float avg;
  static int samplingTime = 0;
  int interval =  2000;

  if(millis()-samplingTime > interval){
    reading = 0;
    for(i = 0; i < 40; i++){
      reading = reading +analogRead(_sensorPin);
      Serial.printf("Reading: %i \n" , reading);
      delayMicroseconds(100);
    }
    avg = reading/40.00;
    Serial.printf("AVG: %.2f \n" , avg);
    samplingTime = millis();
  }
  return avg;
}
float getSlope(float y1value , float y2value , float x1value, float x2value){  //can I even do this I need to think about timing 
      float slope;
      uint16_t slopeAddr = 0xA1;
      slope = (y2value - y1value)/(x2value- x1value);
      float2eeprom(slope, slopeAddr);  //here of void loop? 
      return slope;
}

float getOffset(float yvalue, float xvalue, float slope){
  float offset;
  uint16_t offsetAdd = 0xB1;
  offset = yvalue-(slope*(xvalue));
  float2eeprom(offset, offsetAdd);
  return offset;
}


