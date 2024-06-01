#include <SoftwareSerial.h>
#include <Stepper.h>

SoftwareSerial BTSerial(10, 11); // (Rx, Tx)
const int stepPerRevolution = 2048;
Stepper myStepper(stepPerRevolution, 3, 5, 4, 6);

void setup() {
  myStepper.setSpeed(16);
  Serial.begin(9600);

  BTSerial.begin(9600);
}

int degreeToSteps(int degree) {
  if (degree == 0) return 0;
  return stepPerRevolution / (360 / degree);
}

void loop() {
  if (BTSerial.available()) {
    char data = BTSerial.read();
    Serial.println(data);

    if (data == '1') {
      myStepper.step(degreeToSteps(60));
    }
    else if (data == '0') {
      myStepper.step(-degreeToSteps(120));
    }
    else if (data == '2') {
      myStepper.step(degreeToSteps(180));
    }
    delay(500);

  }
}