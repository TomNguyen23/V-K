#include <Stepper.h>

const int stepPerRevolution = 2048;
Stepper myStepper(stepPerRevolution, 8, 10, 9, 11);

int Joystick_x = A0;
int Joystick_y = A1;
int Joystick_sw = 2;

void setup() {
  myStepper.setSpeed(14);
  Serial.begin(9600); 
  pinMode(Joystick_sw, INPUT_PULLUP);
}

int degreeToSteps(int degree) {
  if (degree == 0) return 0;
  return stepPerRevolution / (360 / degree);
}

void loop() {
  int x, y, sw;
  x = analogRead(Joystick_x);
  y = analogRead(Joystick_y);
  sw = digitalRead(Joystick_sw);

  Serial.print("x = ");
  Serial.print(x);
  Serial.print("\t\t y = ");
  Serial.print(y);
  Serial.print("\t\t sw = ");
  Serial.println(sw);

  if (y > 1000){
    myStepper.step(-degreeToSteps(180));
  }
  if (y < 100) {
    myStepper.step(degreeToSteps(180));
  }
  if (x > 1000) {
    myStepper.step(degreeToSteps(90));
  }
  if (x < 100) {
    myStepper.step(-degreeToSteps(90));
  }
  if (sw == 0) {
    myStepper.setSpeed(20);
    myStepper.step(degreeToSteps(360));
  }

  delay(200);                     
}
