#include <IRremote.hpp>

const int IR_RECEIVE_PIN = 2;
const int LED_PIN = 10;

void setup() {
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
  printActiveIRProtocols(&Serial);

  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if (IrReceiver.decode()) {
    Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);
    if (IrReceiver.decodedIRData.protocol == UNKNOWN) {
      Serial.println(("Unknown"));
    } else {
      IrReceiver.printIRResultShort(&Serial);
      IrReceiver.printIRSendUsage(&Serial);
      if (IrReceiver.decodedIRData.command == 0x1) {
        digitalWrite(LED_PIN, HIGH);
      } else if (IrReceiver.decodedIRData.command == 0x0) {
        digitalWrite(LED_PIN, LOW);
      }
    }
    IrReceiver.resume();
  }
}

