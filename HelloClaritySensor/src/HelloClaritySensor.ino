/*
 * Project HelloClaritySensor
 * Description: Get Clarity Sensor 
 * Author: Micalah Miller
 * Date: 8/15/2022
 */
#include <math.h>
#include "IotTimer.h"

IoTTimer laserTimer; //can I include this in the function?

int laserReading;
int LASERPIN = D12; //LASER PIN FOR TURPIDITY SENSOR
int TURPIN = A5;
unsigned int lastTime, currentTime;

void setup() {
    pinMode(D12, OUTPUT);
    pinMode(A5, INPUT);
    Serial.begin(9600);
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
 // currentTime = millis();
  //if((currentTime - lastTime) > 2000){
  // laserReading = analogRead(A5);
  // Serial.printf("Reading: %i \n" , laserReading);  //voltage increases as resistance decreses when more light is on the photoresistor/ when there is less light the resitance increases and voltage decreases 10k reistor
  // lastTime =  millis();
 // }
  laserTimer.startTimer(5000);
   Serial.printf("Starting Time \n");
  
  turnLaserOn(LASERPIN);
  getTurbidity(TURPIN);
  }
void turnLaserOn(int _digitalPin){  
  //perhaps make a bool function    //laserTimer.startTimer(5000); 
    //Serial.printf("Starting Time \n");
    if(!laserTimer.isTimerReady()){
    digitalWrite(_digitalPin, HIGH);
    Serial.printf("Laser on \n");
    }
    else if(laserTimer.isTimerReady()){
      digitalWrite(_digitalPin, LOW);
      Serial.printf("Laser off \n");
    }
}
  float getTurbidity(int _sensorPin) {  
    //maybe make average its own function and tobidity another one
  float turbidity;
  float _avg;
  int vAnalogRead, i;
  int samplingTime; 
  int _interval = 5000;
  //turnLaserOn(LASERPIN); //just an idea
   if((millis()- samplingTime) > _interval){
    for (i=0; i< 800; i++){
      vAnalogRead = vAnalogRead + analogRead(_sensorPin);
      delayMicroseconds(100);
    }
     _avg = vAnalogRead/800.00;
     Serial.printf("Avg: %.2f \n" ,_avg);
      turbidity = -1185551.78*pow((1/_avg), 2) + 6874.09 * (1/_avg) + 0.091;  
      //quadratic regression for this specific sensor
      //linear regression for data 2 is lowest cloudiness I could find
      Serial.printf("Tur: %.2f \n" , turbidity);
      samplingTime = millis();
   }
  return turbidity;
  }