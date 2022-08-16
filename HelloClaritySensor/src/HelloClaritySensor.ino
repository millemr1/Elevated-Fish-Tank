/*
 * Project HelloClaritySensor
 * Description: Get Clarity Sensor 
 * Author: Micalah Miller
 * Date: 8/15/2022
 */
#include <math.h>
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
  currentTime = millis();
  if((currentTime - lastTime) > 2000){
   laserReading = analogRead(A5);
   Serial.printf("Reading: %i \n" , laserReading);  //voltage increases as resistance decreses when more light is on the photoresistor/ when there is less light the resitance increases and voltage decreases 10k reistor
   lastTime =  millis();
  }
  
  }
void turnLaserOn(int _digitalPin){  //perhaps make a bool function 
  int lastTime;
  if(millis()- lastTime > 5000){
  digitalWrite(_digitalPin, HIGH);
  Serial.printf("Turning laser on \n");
  lastTime = millis();
  }
  else{
    digitalWrite(_digialPin, LOW);
    Serial.printf("Turning laser off \n");
  }
}
  float getTurbidity(int _sensorPin, float _offset, float slope) {
  float turbidity;
  float _avg;
  int vAnalogRead, i;
  int samplingTime; 
  int _interval = 5000;
  turnLaserOn();
   if((millis()- samplingTime) > _interval){
    for (i=0; i< 800; i++){
      vAnalogRead = vAnalogRead + analogRead(_sensorPin);
      delayMicroseconds(100);
    }
    _avg = vAnalogRead/800.00;
    turbidity = -1185551.78*power(_avg, 2) + 6874.09 * _avg + 0.91;
      //linear regression for data 2 is loweres cloudniness
      Serial.printf("Tur: %.2f" , turbidity);
    samplingTime = millis();
  }

  };
