#include <Stepper.h>

const int stepPerRevolution = 2048;
Stepper myStepper(stepPerRevolution, 8, 10, 9, 11);

void setup() {
  myStepper.setSpeed(14);
}

int degreeToSteps(int degree) {
  if (degree == 0) return 0;
  return stepPerRevolution / (360 / degree);
}

void loop() {
  int _degree = degreeToSteps(90);
  myStepper.step(stepPerRevolution);
  delay(1000);
  myStepper.step(-_degree);
  delay(1000);
}
