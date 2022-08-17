/*
 * Project HelloRelay
 * Description: Get relay working
 * Author: Micalah Miller
 * Date: 7/29/2022
 */

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