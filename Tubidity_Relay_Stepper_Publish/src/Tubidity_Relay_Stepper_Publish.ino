/*
 * Project Tubidity_Relay_Stepper_Publish
 * Description: Integrate Basic functionality of my code
 * Author: Micalah Miller
 * Date: 8/18/2022
 */

#include <math.h>
#include "OneWire.h"
#include "spark-dallas-temperature.h"
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT/Adafruit_MQTT.h" 
#include "Adafruit_MQTT/Adafruit_MQTT_SPARK.h"
#include "credentials.h"
//#include "Stepper.h"


TCPClient TheClient; 

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details

//declare pins
const int RELAYPIN = D11;
const int SERVOPIN =  D6;
const int pHPin  =  A4;
 //LASER PIN FOR TURBIDITY SENSOR
const int LASERPIN = D12; 
//photoresistor and 10k ohm resistor reading are being taken
const int TURPIN = A5; 
//pin that temperature sensor is hooked up to
const int oneWireBus = D16; 


bool lightOn, lightOff, foodReady, fishFed, pressed; //check if button is pressed from the dashboard
int lastTime;
int feedHour = 11, feedMin =  27;
 //i may not makes these global forever, but for now this works
float TUR, temp, phVal;
int pos = 180, pos2 = 0;  //position of servo motor

//calibrated values specific to sensor
float phSlope = -88.31; //put in eeprom calibration later to reduce global variable count by quite a bit
float offset = 2935.00;
//check if button is pressed from the dashboard

//declare objects
Servo myServo;
OneWire oneWire(oneWireBus); 
DallasTemperature fishTemp(&oneWire);
Adafruit_MQTT_SPARK mqtt(&TheClient,AIO_SERVER,AIO_SERVERPORT,AIO_USERNAME,AIO_KEY); 
Adafruit_MQTT_Subscribe mqttObjFeedManually = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/feedfish");  


//Stepper myStepper(STEPSPERREVOLUTION, D6, D4, D5, D3);  

void setup() {
  Serial.begin(9600);
  waitFor(Serial.isConnected, 15000); 

  Time.zone(-6);  //MDT
  Particle.syncTime();

   //Connect to WiFi without going to Particle Cloud
  WiFi.connect();
  while(WiFi.connecting()) {
    Serial.printf("."); 
  }

  mqtt.subscribe(&mqttObjFeedManually);

  pinMode(RELAYPIN, OUTPUT);  //pinModes for circuits
  pinMode(LASERPIN, OUTPUT);
  pinMode(TURPIN, INPUT);
  pinMode(pHPin, INPUT);

  myServo.attach(SERVOPIN);
  myServo.write(pos);
 // myStepper.setSpeed(15);  //15 revolutions per minute
  fishTemp.begin();
}
void loop() {
  Serial.printf("servo angle %i \n" , myServo.read());
   MQTT_connect();
  foodReady = setTime(feedHour, feedMin);  //military time
  fishFed =  setTime(feedHour, feedMin + 1);   //1 minute aferwards if this happens on the hour code wonr run need to fix that
  lightOn = setTime(11, 24);   //two variables
  lightOff = setTime(11, 26);
  pressed = IsButtonOnDashPressed(); //maybe get rid or pressed and put it in the if statement? 

    if(pressed){ //check if button on dash is pressed
     Serial.printf("servo angle %i \n" , myServo.read());
      myServo.write(pos2);  //out
      delay(1000);
      myServo.write(pos);  //in
    }
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
  if(millis() -  lastTime > 20000){
    temp =  getTemp(); //maybe commment these out
    phVal = readPH(pHPin, offset, phSlope);
    publishPHandTemp();
    lastTime = millis();
    publishTurbidity();// maybe put this elsewhere
    
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
    phReading = 0;  //initialize variable so that it starts at 0 or else ph will get messed up;
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
void MQTT_connect() {
  int8_t ret;
  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }
 
  Serial.print("Connecting to MQTT... ");
 
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
       Serial.printf("%s\n",(char *)mqtt.connectErrorString(ret));
       Serial.printf("Retrying MQTT connection in 5 seconds..\n");
       mqtt.disconnect();
       delay(5000);  // wait 5 seconds
  }
  Serial.printf("MQTT Connected!\n");
}
bool publishPHandTemp(){  //these can publish at same time Tubridity is on its own timer becuase of the laser 
  Adafruit_MQTT_Publish mqttObjTankTemp = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/tanktemp");
  Adafruit_MQTT_Publish mqttObjPH = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/phdata");
  float _PH = readPH(pHPin, offset, phSlope); //yes these are global variables, but all of these things can be altered at the top
  float _temp = getTemp(); //there might be a better way to do this
  bool published;  //make static?


  if(mqtt.Update()){
    mqttObjTankTemp.publish(_temp);
    mqttObjPH.publish(_PH);
    Serial.printf("Publishing Temp: %.2f \n, Publishing PH: %.2f \n" , _temp , _PH); 
    published = true ;
  }
  else{
    published = false;
    Serial.printf(" Nothing Published \n"); 
  }
  return published;
}
bool publishTurbidity(){  //I may need to do this in the tur function we'll see
  Adafruit_MQTT_Publish mqttObjClarity = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/turbidity");
  bool published; //static?
  float _turbidity = readTurbidity(TURPIN);  //also global for the sake of readibility. the pin can change and it is eaier to alter in one plae rather than 1

  if(mqtt.Update()){
    mqttObjClarity.publish(_turbidity);
    Serial.printf("Publishing Tur: %.2f \n" , _turbidity); 
    published = true ;
  }
  else{
    published = false;
    Serial.printf(" Tur did not Publish \n"); 
  }
  return published;
}
bool IsButtonOnDashPressed(){
  float buttonState;
  bool isButtonState;
   Adafruit_MQTT_Subscribe * subscription;
  while(subscription = mqtt.readSubscription(200)){
    if(subscription == &mqttObjFeedManually){
      buttonState = atof((char *)mqttObjFeedManually.lastread);
      Serial.printf("Received %0.2f from Adafruit.io feed /feedfish \n", buttonState);     
    }
  }
    if(buttonState == 1.00){
      isButtonState = true;
      Serial.printf("button is on \n");
    }
    else if (buttonState == 0.00){
      isButtonState = false;
       Serial.printf("button is off \n");
     }
    return isButtonState;
}