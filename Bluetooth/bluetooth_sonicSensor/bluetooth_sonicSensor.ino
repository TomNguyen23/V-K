#include <SoftwareSerial.h>

SoftwareSerial BTSerial(10, 11); // (Rx, Tx)
const int trigPin = 5;
const int echoPin = 3;
long duration;
int distance;

void setup() {
  Serial.begin(9600);
  BTSerial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  distance = duration * 0.034 / 2;

  if(distance >= 10 && distance <= 20) BTSerial.write("0");
  else if(distance < 10) BTSerial.write("1");
  else BTSerial.write("2");

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println("cm");

  delay(1000);
}
