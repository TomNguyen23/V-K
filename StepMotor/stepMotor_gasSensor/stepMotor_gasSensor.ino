#include <Stepper.h>

const int stepPerRevolution = 2048;
Stepper myStepper(stepPerRevolution, 8, 10, 9, 11);

int const PINO_SGAS = A0;

void setup() {
  myStepper.setSpeed(14);
  Serial.begin(9600); 
}

int degreeToSteps(int degree) {
  if (degree == 0) return 0;
  return stepPerRevolution / (360 / degree);
}

void loop() {
  int val = analogRead(PINO_SGAS);
  Serial.println(val, DEC);

  if (val > 450){
    myStepper.step(degreeToSteps(60));
  }
  else {
    myStepper.step(-degreeToSteps(90));
  }
  delay(200);                     
}
