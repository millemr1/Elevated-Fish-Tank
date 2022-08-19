/*
 * Project Tubidity_Relay_Stepper_Publish
 * Description: Integrate Basic functionality of my code
 * Author: Micalah Miller
 * Date: 8/18/2022
 */

#include <math.h>
#include "Stepper.h"

const int STEPSPERREVOLUTION = 2048;
int RELAYPIN = D11;
bool lightOn, lightOff, foodReady;
int LASERPIN = D12; //LASER PIN FOR TURPIDITY SENSOR
int TURPIN = A5;  //i may not makes these global forever, but for now this works
float TUR;

//declare objects
Stepper myStepper(STEPSPERREVOLUTION, D6, D4, D5, D3);

void setup() {
  
  Time.zone(-6);  //MDT
  Particle.syncTime(); 
  
  pinMode(RELAYPIN, OUTPUT);  //pinModes for circuits
  pinMode(LASERPIN, OUTPUT);
  pinMode(TURPIN, INPUT);

  myStepper.setSpeed(15);  //15 revolutions per minute
  
  Serial.begin(9600);
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  foodReady = setTime(17, 28);  //military time
  lightOn = setTime(17, 26);   //two vai
  lightOff = setTime(17, 27);

   if(foodReady){
   myStepper.step(-512);  //about 90 degrees 25% of 360
    delay(250);
    myStepper.step(512);  
    Serial.print("Food Ready \n");
     }
    if(lightOn){
      digitalWrite(RELAYPIN, HIGH);
      Serial.printf(" Aq On \n");
    }
    else if(lightOff){
      digitalWrite(RELAYPIN, LOW);
      Serial.printf("AQ Off \n");
    }

  TUR = readTurbidity(TURPIN); //this may interfear with other code since I have it reading every 15 minutes right now
  Serial.printf( "Tur: \n" , TUR);
}
bool setTime(int _setHours, int _setMinutes){ 
  bool timeReady = false;
  int currentTime = (Time.hour()*60)+(Time.minute());  //convert to minute
  Serial.printf("Current Time: %i \n", currentTime);
  int setTime = (_setHours*60)+_setMinutes;  //convert time into minutes?  
   Serial.printf("Set Time: %i \n" ,setTime);

      if(currentTime == setTime){  
      if(Time.second() <= 2){  //only want it to happen on the second not not the whole minute
      timeReady = true;
      Serial.printf("Time Ready \n");
      }
    }
    return timeReady;
   }
float readTurbidity(int _sensorPin) {  
    //maybe make average its own function and tobidity another one
  static float turbidity;
  static float samplingTime; 
  float _median;
  int vAnalogRead[100]; 
  int i = 0;
  int _interval = 30000;  //for 900000 milliseconds for 15 minutes 
   if((millis()- samplingTime) > _interval){
      digitalWrite(LASERPIN, HIGH);  //make this local soon
      Serial.printf(" Laser On");
    for (i=0; i< 100; i++){
      Serial.printf("i: %i \n" , i);
      vAnalogRead[i] = analogRead(_sensorPin);
      delayMicroseconds(100);
    }
      digitalWrite(LASERPIN, LOW);
      Serial.printf("Median getting \n");
      _median = getMedian(vAnalogRead, 100);  //maybe convert to voltage value
      Serial.printf( "Med: %.2f \n" , _median);
      turbidity = -1185551.78*pow((1/_median), 2) + 6874.09 * (1/_median) + 0.091; 
      //EEPROM maybe
      //magic numbers meaningless numbers
      //quadratic regression for this specific sensor
      //linear regression for data 2 is lowest cloudiness I could find
      Serial.printf("Tur: %.2f \n" , turbidity);
      //samplingTime = millis();
   }
  return turbidity;
  }

int getMedian(int array1[], int  arrayLen) {  
  int array1Tab[arrayLen];  
  int i, j, arrayTemp;
  for (byte i = 0; i < arrayLen; i++){
    //array Len  is the number of times being sampled in my case 800
    array1Tab[i] = array1[i];  //making copy of array
    Serial.printf("Arr: %i \n" , i);
  }  //does this tab go here?
  for (j = 0; j < arrayLen - 1; j++){ //take largest number and move it to end of the array //tells you how many elements in the array from the end have been ordered
      Serial.printf("J: %i \n" , j);
    for (i = 0; i < arrayLen- j - 1; i++) {  //for each index go through previous indexes
      if (array1Tab[i] > array1Tab[i + 1]){   
        // if some number is greater than the next
        arrayTemp = array1Tab[i];  
        array1Tab[i] = array1Tab[i + 1];  //swap values in i and i+i places of array
        array1Tab[i + 1] = arrayTemp;   
        Serial.printf("ORDERING: %i \n" , array1Tab[i]);
      }
    Serial.printf("Arr tab: %i \n Array Temp: %i \n" , array1[i], arrayTemp);
    }
  }
  if ((arrayLen & 1) > 0){ //checks if odd
    arrayTemp = array1Tab[(arrayLen - 1) / 2]; //take to middle most number because the array is ordered
  }
  else{  //i added these brackets 
    arrayTemp = (array1Tab[arrayLen/ 2] + array1Tab[arrayLen / 2 - 1]) / 2;  //average if even middle becuase the array is ordered 
  }
   return arrayTemp;
}