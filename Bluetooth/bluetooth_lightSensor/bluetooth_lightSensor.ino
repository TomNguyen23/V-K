#include <SoftwareSerial.h>

SoftwareSerial BTSerial(10, 11); // (Rx, Tx)

int lightPin = A0;

void setup() {
  Serial.begin(9600);

  Serial.println("Master is ready!");
  BTSerial.begin(9600);
}
void loop() {
  int val = analogRead(lightPin);
  Serial.print("Light Sensor Value: ");
  Serial.println(val);

  if (val > 200) BTSerial.write('1');
  else BTSerial.write('0');

  delay(1000);
}