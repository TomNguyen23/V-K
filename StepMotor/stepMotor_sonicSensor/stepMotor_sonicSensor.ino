#include <Stepper.h>

const int stepPerRevolution = 2048;
Stepper myStepper(stepPerRevolution, 8, 10, 9, 11);

const int trigPin = 5;
const int echoPin = 3;
long duration;
int distance;

void setup() {
  myStepper.setSpeed(14);
  Serial.begin(9600); 
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

int degreeToSteps(int degree) {
  if (degree == 0) return 0;
  return stepPerRevolution / (360 / degree);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  distance = duration * 0.034 / 2;

  if (distance >= 10 && distance <= 20){
    myStepper.step(degreeToSteps(60));
  }
  else if (distance < 10) {
    myStepper.step(0);
  } else {
    myStepper.step(-degreeToSteps(90));
  }

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println("cm");
  delay(200);                     
}
