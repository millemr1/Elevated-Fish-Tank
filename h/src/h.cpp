/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "/Users/Layla2/Documents/IoT/Elevated-Fish-Tank/h/src/h.ino"
/*
 * Project Stepper and Relay
 * Description: Get Relay and Stepper working on a timer
 * Author: Micalah Miller
 * Date: 8/17/2022
 */
#include "Stepper.h"

void setup();
void loop();
#line 9 "/Users/Layla2/Documents/IoT/Elevated-Fish-Tank/h/src/h.ino"
const int STEPSPERREVOLUTION = 2048;

Stepper myStepper(STEPSPERREVOLUTION, D6, D4, D5, D3);  ////Declare pins out of order becayse library is messed up a bit (didn't have time to write my own)

void setup() {

  Serial.begin(9600);    
  myStepper.setSpeed(15);  //15 revolutions per minute
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
    myStepper.step(512);  //about 45 degrees
    delay(500);
    myStepper.step(-512);

}