#include <SoftwareSerial.h>

SoftwareSerial BTSerial(10, 11); // (Rx, Tx)
int const PINO_SGAS = A0;

void setup() {
  Serial.begin(9600);
  BTSerial.begin(9600);

}

void loop() {
  int val = analogRead(PINO_SGAS);
  Serial.println(val, DEC);
  delay(1000);

  if (val >= 300) {
    BTSerial.write("1");
  } else {
    BTSerial.write("0");
  }

}
