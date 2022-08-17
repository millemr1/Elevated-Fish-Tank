/*
 * Project Stepper and Relay
 * Description: Get Relay and Stepper working on a timer
 * Author: Micalah Miller
 * Date: 8/17/2022
 */
#include "Stepper.h"

const int STEPSPERREVOLUTION = 2048;

Stepper myStepper(STEPSPERREVOLUTION, D6, D4, D5, D3);  ////Declare pins out of order becayse library is messed up a bit (didn't have time to write my own)

void setup() {
  Time.zone(-6);  //MDT
  Particle.syncTime(); 
  Serial.begin(9600);    
  myStepper.setSpeed(15);  //15 revolutions per minute


}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
    if()
    myStepper.step(512);  //about 45 degrees
    delay(500);
    myStepper.step(-512);

}

bool setTime(int _setHours, int _setMinutes , int  _desiredtime){  //I think this method will work for the laser this feels like too much
    bool timeReady = false;
    int currentTime = (Time.hour()*60)+(Time.minute())  //conveert to minute
    Serial.printf("Current Time: %i \n", currentTime);
    int setTime = (_setHours*60)+_setMinutes  //convert time into minutes?  should I do somthing with the seconds?
    Serial.printf("Set Time: %i \n" ,setTime);

    if(currentTime == setTime){  
      if(Time.second() < 2){  //only want it to happen on the seconds not the whole minute
      timeReady = true;
      Serial.printf("Time Ready");
      }
    }
    return timeReady;
}