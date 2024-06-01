#include <Servo.h>

Servo myServo;
const int SERVO_PIN = 9;
const int trigPin = 5;
const int echoPin = 3;
long duration;
int distance;

int state = 0;

void setup() {
  myServo.attach(SERVO_PIN);
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {  
  if(state == 0) {
    state = 1;
    myServo.write(0);
  }
  else {
    state = 0;
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    duration = pulseIn(echoPin, HIGH);

    distance = duration * 0.034 / 2;

    if(distance >= 10 && distance <= 20) myServo.write(90);
    else if(distance < 10) myServo.write(30);
    else myServo.write(150);
  }

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println("cm");

  delay(800);

}
