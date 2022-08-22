/*
 * Project Tubidity_Relay_Stepper_Publish
 * Description: Integrate Basic functionality of my code
 * Author: Micalah Miller
 * Date: 8/18/2022
 */

#include <math.h>
#include "OneWire.h"
#include "spark-dallas-temperature.h"
//#include "Stepper.h"

//declare pins
int RELAYPIN = D11;
int SERVOPIN =  D6;
const int pHPin  =  A4;
int LASERPIN = D12; //LASER PIN FOR TURPIDITY SENSOR
int TURPIN = A5; //photoresistor and 10k ohn resistor reading are being taken

const int oneWireBus = D16; //pin that temperature sensor is hooked up to

bool lightOn, lightOff, foodReady, fishFed;
int lastTime;
int feedHour = 13, feedMin =  02;
 //i may not makes these global forever, but for now this works
float TUR, temp;
int pos = 180, pos2 = 0;  //position of servo motor

//calibrated values specific to sensor
float phSlope = -88.31; //put in eeprom calibration later to reduce global variable count by quite a bit
float offset = 2935.00;
float phVal;

//declare objects
Servo myServo;
OneWire oneWire(oneWireBus); 
DallasTemperature fishTemp(&oneWire);
//Stepper myStepper(STEPSPERREVOLUTION, D6, D4, D5, D3);  

void setup() {
  Serial.begin(9600);

  Time.zone(-6);  //MDT
  Particle.syncTime(); 
  
  pinMode(RELAYPIN, OUTPUT);  //pinModes for circuits
  pinMode(LASERPIN, OUTPUT);
  pinMode(TURPIN, INPUT);
  pinMode(pHPin, INPUT);

  myServo.attach(SERVOPIN);
  myServo.write(pos);
 // myStepper.setSpeed(15);  //15 revolutions per minute

}

void loop() {
  foodReady = setTime(feedHour, feedMin);  //military time
  fishFed =  setTime(feedHour, feedMin + 1);   //1 minute aferwards if this happens on the hour code wonr run need to fix that
  lightOn = setTime(11, 29);   //two variables
  lightOff = setTime(17, 31);

   if(foodReady){
    myServo.write(pos2);  //I want my gear moving in opposite direction so I write it to zero

    Serial.print("Food Ready \n");
     }
    if(fishFed){  
      myServo.write(pos);  //reset servo
      Serial.printf("Resetting \n");
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
  if(millis() -  lastTime > 10000){
    temp =  getTemp(); 
    phVal = readPH(pHPin, offset, phSlope);
    lastTime = millis();
  }
  ///Serial.printf( "Tur: \n" , TUR);
}
bool setTime(int _setHours, int _setMinutes){ 
  bool timeReady = false;
  int currentTime = (Time.hour()*60)+(Time.minute());  //convert to minute
 // Serial.printf("Current Time: %i \n", currentTime);
  int setTime = (_setHours*60)+_setMinutes;  //convert time into minutes?  
   //Serial.printf("Set Time: %i \n" ,setTime);

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
      //EEPROM maybe for A,B, and C
      //magic numbers meaningless numbers
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
  if ((arrayLen & 1) > 0){ //checks if arrayLen isodd
    arrayTemp = array1Tab[(arrayLen - 1) / 2]; //take to middle most number because the array is ordered
  }
  else{  //i added these brackets 
    arrayTemp = (array1Tab[arrayLen/ 2] + array1Tab[arrayLen / 2 - 1]) / 2;  //average if even middle becuase the array is ordered 
  }
   return arrayTemp;
}
float getTemp(){  //publish here?
  float _fishTemp;

  fishTemp.requestTemperatures();  
  _fishTemp = fishTemp.getTempCByIndex(0);
  Serial.printf("Celsius temperature: %.2f \n" , _fishTemp);
  return _fishTemp;
}
float readPH(int _sensorPin, float _offset, float  _slope){
  static float PH;
  float _avg;
  int phReading, i;
  static int samplingTime;
  int _interval = 2000; 

  if (millis()- samplingTime > _interval){
    for(i = 0; i < 40; i++){
      phReading = phReading + analogRead(_sensorPin);  //store new readings plus old readings 
      Serial.printf("phReading: %i \n" , phReading);
      delayMicroseconds(100);
    }
    _avg = phReading/40.00;
    Serial.printf("AVG: %.2f \n" ,_avg);
    PH  = (_avg - _offset)/_slope;
    Serial.printf("PH: %.2f \n" , PH);
    samplingTime = millis();
  }
  return PH;
}