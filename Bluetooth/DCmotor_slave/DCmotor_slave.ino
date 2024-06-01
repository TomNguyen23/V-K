#include <SoftwareSerial.h>

SoftwareSerial BTSerial(10, 11); // (Rx, Tx)

#define maxSpeed  255
#define minSpeed  0
int step = 10;
int ENA = 3;
int IN1 = 4;
int IN2 = 5;

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  Serial.begin(9600);
  BTSerial.begin(9600);
}

void loop() {
  if (BTSerial.available()) {
    char data = BTSerial.read();
    Serial.println(data);

    if (data == '1') {
      analogWrite(ENA, maxSpeed);
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);

    }
    else if (data == '0') {
      analogWrite(ENA, maxSpeed);
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
    }
  }

}
