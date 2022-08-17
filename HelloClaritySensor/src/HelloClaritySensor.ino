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

void loop() {
 // currentTime = millis();
  //if((currentTime - lastTime) > 2000){
  // laserReading = analogRead(A5);
  // Serial.printf("Reading: %i \n" , laserReading);  //voltage increases as resistance decreses when more light is on the photoresistor/ when there is less light the resitance increases and voltage decreases 10k reistor
  // lastTime =  millis();
 // }
  laserTimer.startTimer(5000);
   Serial.printf("Starting Time \n");

  getTurbidity(TURPIN);
    
}
  float Turbidity(int _sensorPin) {  
    //maybe make average its own function and tobidity another one
  static float turbidity;
  static float samplingTime; 
  float _median;
  int vAnalogRead[], i; 
  int _interval = 30000;  //for testing purposes
  //turnLaserOn(LASERPIN); //just an idea
   if((millis()- samplingTime) > _interval){
    for (i=0; i< 800; i++){
      vAnalogRead[i] = analogRead(_sensorPin);
      delayMicroseconds(100);
    }
      median[i] = vAnalogRead/800.00;
      Serial.printf("Avg: %.2f \n" ,_avg);
      turbidity = -1185551.78*pow((1/_avg), 2) + 6874.09 * (1/_avg) + 0.091;  
      //quadratic regression for this specific sensor
      //linear regression for data 2 is lowest cloudiness I could find
      Serial.printf("Tur: %.2f \n" , turbidity);
      samplingTime = millis();
   }
  return turbidity;
  }

  //float turpidity();  //rewriting 
      //float tubidity;


int getMedian(int array1[], int  arrayLen) {  //treat like pointer?
  //tabulates the reading in array and divides by total readings to smooth out variabilities
  int array1Tab[arrayLen];  
  int i, j, arrayTemp;
      //array1tab identifies the tabulated sum of readings stored
  for (byte i = 0; i < arrayLength; i++){
    //array Len  is the number of times being sampled in my case 800
    array1tab[i] = array[i];  //making copy of array for some reason
  }  //does this tab go here?
  for (j = 0; j < arrayLength - 1; j++){ //take largest number and move it to end of the array //tells you how many elements in the array from the end have been ordered
    for (i = 0; i < arrayLength - j - 1; i++) {  //for each index go through previous indexes
      if (array1Tab[i] > array1Tab[i + 1]){   
        // if some number is greater than the next
        arrayTemp = array1Tab[i];  
        array1Tab[i] = array1Tab[i + 1];  //swap values in i and i+i places of array
        array1Tab[i + 1] = arrayTemp;   
      }
    Serial.printf("Arr tab: %i \n Array Temp: %i \n" , array1[i], arrayTemp);
    }
  }
  if ((arrayLen & 1) > 0){  //checks if even/odd  //if array Len and 1 are greater than 0?
    arrayTemp = array1Tab[(arrayLen - 1) / 2]; //subtract 1 due to the number of array starting at 0, and check if it in 
  }
  else{  //i added these brackets 
    arrayTemp = (array1Tab[arrayLen/ 2] + array1Tab[arrayLen / 2 - 1]) / 2;
  }
   return arrayTemp;
}