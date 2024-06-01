#include <SoftwareSerial.h>

SoftwareSerial BTSerial(10, 11); // (Rx, Tx)
void setup() {
  pinMode(5, OUTPUT);
  digitalWrite(5, HIGH);
  Serial.begin(9600);
  Serial.println("Enter AT Commands:");
  BTSerial.begin(38400);
}
void loop() {
  if (BTSerial.available())
  Serial.write(BTSerial.read());
  if (Serial.available())
  BTSerial.write(Serial.read());
}