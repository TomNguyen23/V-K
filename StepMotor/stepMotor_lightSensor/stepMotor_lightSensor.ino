#include <Stepper.h>

const int stepPerRevolution = 2048;
Stepper myStepper(stepPerRevolution, 8, 10, 9, 11);

int light = A0;
int val = 0;

void setup() {
  myStepper.setSpeed(15);
  Serial.begin(9600);
}

int degreeToSteps(int degree) {
  if (degree == 0) return 0;
  return stepPerRevolution / (360 / degree);
}

void loop() {
  val = analogRead(light);
  Serial.println(val);
  
  if (val < 150) {
    myStepper.step(degreeToSteps(45));
  } else {
    myStepper.step(-degreeToSteps(90));
  }
  delay(200);
}
