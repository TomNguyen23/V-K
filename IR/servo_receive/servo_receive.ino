#include <IRremote.hpp>
#include <Servo.h>

Servo myServo;
const int irPin = 2;
const int SERVO_PIN = 9;

void setup() {
  myServo.attach(SERVO_PIN);
  Serial.begin(9600);
  IrReceiver.begin(irPin, ENABLE_LED_FEEDBACK);
  printActiveIRProtocols(&Serial);
}

void loop() {
  if (IrReceiver.decode()) {
    if (IrReceiver.decodedIRData.protocol == UNKNOWN) {
      Serial.println(("Unknown"));
    } else {
      IrReceiver.printIRResultShort(&Serial);
      IrReceiver.printIRSendUsage(&Serial);
      if (IrReceiver.decodedIRData.command == 0x1) {
        myServo.write(90);
        delay(200);
        myServo.write(0);
      } else if (IrReceiver.decodedIRData.command == 0x0) {
        myServo.write(180);
        delay(200);
        myServo.write(0);
      }
      delay(500);
    }
    IrReceiver.resume();
  }

}
