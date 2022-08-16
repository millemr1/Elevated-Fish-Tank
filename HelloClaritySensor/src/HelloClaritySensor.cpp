/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "/Users/Layla2/Documents/IoT/Elevated-Fish-Tank/HelloClaritySensor/src/HelloClaritySensor.ino"
/*
 * Project HelloClaritySensor
 * Description: Get Clarity Sensor 
 * Author: Micalah Miller
 * Date: 8/15/2022
 */

void setup();
void loop();
#line 8 "/Users/Layla2/Documents/IoT/Elevated-Fish-Tank/HelloClaritySensor/src/HelloClaritySensor.ino"
int laserReading;
unsigned int lastTime, currentTime;
void setup() {
    pinMode(D12, OUTPUT);
    pinMode(A5, INPUT);
    Serial.begin(9600);
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  currentTime = millis();
  if((currentTime - lastTime) > 2000){
   laserReading = analogRead(A5);
   Serial.printf("Reading: %i \n" , laserReading);
   lastTime =  millis();
  }
   
    
  }