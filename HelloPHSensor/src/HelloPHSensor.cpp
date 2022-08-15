/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "/Users/Layla2/Documents/IoT/Elevated-Fish-Tank/HelloPHSensor/src/HelloPHSensor.ino"
/*
 * Project HelloPHSensor
 * Description: Get Grove PH sensor working from and analog reading
 * Author: Micalah Miller
 * Date: 8/15/2022
 */

void setup();
void loop();
int takePhReading();
#line 8 "/Users/Layla2/Documents/IoT/Elevated-Fish-Tank/HelloPHSensor/src/HelloPHSensor.ino"
const int pHPin =  A4;
const int offset = 41; //will need to calculate later for my specfic sensor for 
const int LED = D7;
const int sampleInterval = 20;
const int printInterval = 800;  //not quite sure what this is for yet
const int phArrayLength = 40;
int phArray[phArrayLength];  //average the values of the reading for a more statistically accurate result
int i = 0;

void setup() {
  pinMode(LED, OUTPUT);
  //pinMode(pHpin, INPUT);
  Serial.begin(9600);

}

void loop() {
  // The core of your code will likely live here.

}

int takePhReading(){
  static unsigned long samplingTime = millis();
  static unsigned long  printTime = millis();
  static float pHValue, voltage;
  if(millis()- samplingTime > sampleInterval){  
     //this feels like a lot for one line of code
     pHArray[i++] = analogRead(pHpin); 
     if(phArrayLength == 40){
      i = 0;  //reset the index
      voltage = averagearray()
     }



  }
}