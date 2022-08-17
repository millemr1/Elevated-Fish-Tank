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
int LASERPIN = A2; //LASER PIN FOR TURPIDITY SENSOR
int TURPIN = A4;
unsigned int lastTime, currentTime;
float TUR;

void setup() {
    pinMode(A2, OUTPUT);
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
  TUR = readTurbidity(TURPIN);

  //Serial.printf("Tubdidity: %.f \n" , TUR);
}
  float readTurbidity(int _sensorPin) {  
    //maybe make average its own function and tobidity another one
  static float turbidity;
  static float samplingTime; 
  float _median;
  int vAnalogRead[100]; 
  int i = 0;
  int _interval = 30000;  //for testing purposes
   //just an idea
   if((millis()- samplingTime) > _interval){
      digitalWrite(LASERPIN, HIGH);
      Serial.printf(" Laser On");
    for (i=0; i< 100; i++){
      Serial.printf("i: %i" , i);
      vAnalogRead[i] = analogRead(_sensorPin);
      delayMicroseconds(100);
    }
      digitalWrite(LASERPIN, LOW);
      Serial.printf("Median getting \n");
      _median = getMedian(vAnalogRead, 100);  //maybe convert to voltage value
      Serial.printf( "Med: %.2f \n" , _median);
      turbidity = -1185551.78*pow((1/_median), 2) + 6874.09 * (1/_median) + 0.091;   //QUADRATIC REGRESSION INVERSSED BECAUSE WE WANT A 
      //quadratic regression for this specific sensor
      //linear regression for data 2 is lowest cloudiness I could find
      Serial.printf("Tur: %.2f \n" , turbidity);
      samplingTime = millis();
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
    arrayTemp = array1Tab[(arrayLen - 1) / 2]; //subtract 1 due to the number of array starting at 0, and check if it in 
  }
  else{  //i added these brackets 
    arrayTemp = (array1Tab[arrayLen/ 2] + array1Tab[arrayLen / 2 - 1]) / 2;
  }
   return arrayTemp;
}