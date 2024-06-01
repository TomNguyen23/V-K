#include <SoftwareSerial.h>

SoftwareSerial BTSerial(10, 11); // (Rx, Tx)

int linePin = 3;

void setup() {
  Serial.begin(9600);

  Serial.println("Master is ready!");
  BTSerial.begin(9600);
}
void loop() {
  int val = digitalRead(linePin);
  Serial.println(val);

  if (val == 1) BTSerial.write('1');
  else BTSerial.write('0');

  delay(1000);
}