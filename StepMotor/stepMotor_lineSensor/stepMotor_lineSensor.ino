#include <Stepper.h>

const int stepPerRevolution = 2048;
Stepper myStepper(stepPerRevolution, 8, 10, 9, 11);

int line = 13;
int val = 0;

void setup() {
  myStepper.setSpeed(14);
  Serial.begin(9600);
  pinMode(line, INPUT);
}

int degreeToSteps(int degree) {
  if (degree == 0) return 0;
  return stepPerRevolution / (360 / degree);
}

void loop() {
  val = digitalRead(line);
  Serial.println(val);
  
  if (val == 0) {
    myStepper.step(degreeToSteps(60));
  } else {
    myStepper.step(-degreeToSteps(90));
  }
  delay(200);
}
