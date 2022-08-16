/*
 * Project HelloPHSensor
 * Description: Get Grove PH sensor working from and analog reading
 * Author: Micalah Miller
 * Date: 8/15/2022
 */

const int pHPin  =  A4;
float phSlope = -80.575;
float offset = 2822.62;
float phVal;
void setup() {
  pinMode(pHPin, INPUT);
  Serial.begin(9600);
}
void loop() {
  //analog = analogRead(pHPin);
  //Serial.printf("Analog: %i \n" , analog);
  //phVal = (analog - 2822.62)/(-80.575);
  //Serial.printf("PH: %.3f \n" , phVal);

  phVal = readPH(pHPin, offset, phSlope);
 //Serial.printf("PH VAL: %.2f \n" , phVal);
}
float readPH(int _sensorPin, float _offset, float  _slope){
  float PH;
  int phReading, i;
  static int samplingTime;
  int _interval = 2000; 

  if (millis()- samplingTime > _interval){
    for(i = 0; i < 40; i++){
      phReading = analogRead(_sensorPin);
      delayMicroseconds(100);
    }
    _avg = phReading/40;
    PH  = (_avg - _offset)/_slope;
    Serial.printf("PH: %.2f \n" , PH);
    samplingTime = millis();
  }
  return PH;
}