/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "/Users/Layla2/Documents/IoT/Elevated-Fish-Tank/tempsensor/src/tempsensor.ino"
/*
 * Project tempsensor 
 * Description: Get Temperature Sensor Working
 * Author: Micalah Miller
 * Date: 8/22/2022
 *
 * */

#include "OneWire.h"
#include "spark-dallas-temperature.h"

void setup();
void loop();
#line 12 "/Users/Layla2/Documents/IoT/Elevated-Fish-Tank/tempsensor/src/tempsensor.ino"
const int oneWireBus = D16; //analog?
int numberOfDevices;

OneWire oneWire(oneWireBus);

DallasTemperature fishTemp(&oneWire);

void setup() {
  Serial.begin(9600);
  fishTemp.begin();
}

void loop() {
	// Call sensors.requestTemperatures() to issue a global temperature and Requests to all devices on the bus
  fishTemp.requestTemperatures(); 

  Serial.print("Celsius temperature: ");
  // Why "byIndex"? You can have more than one IC on the same bus. 0 refers to the first IC on the wire
  Serial.print(fishTemp.getTempCByIndex(0)); 
  Serial.print(" - Fahrenheit temperature: ");
  Serial.println(fishTemp.getTempFByIndex(0));
  delay(1000);

}

