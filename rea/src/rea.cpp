/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "/Users/Layla2/Documents/IoT/Elevated-Fish-Tank/rea/src/rea.ino"
/*
 * Project HelloRelay
 * Description: Get relay working
 * Author: Micalah Miller
 * Date: 7/29/2022
 */

void setup();
void loop();
#line 8 "/Users/Layla2/Documents/IoT/Elevated-Fish-Tank/rea/src/rea.ino"
int relayPin = 11;

void setup() {
  pinMode(relayPin, OUTPUT);
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  digitalWrite(relayPin, HIGH);
  delay(500);
  digitalWrite(relayPin, LOW);
  delay(10);
}