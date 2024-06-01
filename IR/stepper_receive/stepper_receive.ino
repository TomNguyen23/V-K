#include <IRremote.hpp>
#include <Stepper.h>

const int stepPerRevolution = 2048;
Stepper myStepper(stepPerRevolution, 8, 10, 9, 11);

const int irPin = 2;

void setup() {
  myStepper.setSpeed(14);
  Serial.begin(9600);
  IrReceiver.begin(irPin, ENABLE_LED_FEEDBACK);
  printActiveIRProtocols(&Serial);
}


int degreeToSteps(int degree) {
  if (degree == 0) return 0;
  return stepPerRevolution / (360 / degree);
}

void loop() {
  if (IrReceiver.decode()) {
    if (IrReceiver.decodedIRData.protocol == UNKNOWN) {
      Serial.println(("Unknown"));
    } else {
      IrReceiver.printIRResultShort(&Serial);
      IrReceiver.printIRSendUsage(&Serial);
      if (IrReceiver.decodedIRData.command == 0x1) {
        myStepper.step(degreeToSteps(60));
      } else if (IrReceiver.decodedIRData.command == 0x0) {
        myStepper.step(-degreeToSteps(120));
      }
      delay(500);
    }
    IrReceiver.resume();
  }

}
