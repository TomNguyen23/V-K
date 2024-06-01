#include <IRremote.hpp>  
 
const int trigPin = 5;
const int echoPin = 3;
long duration;
int distance;

int irPin = 9;
uint16_t address = 0x0;
uint16_t command;
uint16_t repeat = 0;

void setup() {
  IrSender.begin(irPin);
  IrSender.enableIROut(38);

  Serial.begin(9600);
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

  Serial.print("distance: ");
  Serial.println(distance);

  if(distance >= 10 && distance <= 20) {
    command = 0x1;
  }
  else {
    command = 0x0;
  }

  Serial.println(command, HEX);
  IrSender.sendRC5(address, command, repeat, false);
  delay(1000);
}
