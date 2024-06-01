#include <IRremote.hpp>

const int irPin = 2;

#define maxSpeed  255
#define minSpeed  0
int step = 10;
int ENA = 3;
int IN1 = 4;
int IN2 = 5;

void setup() {
  Serial.begin(9600);
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
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
      if (IrReceiver.decodedIRData.command == 0x0) {
        analogWrite(ENA, maxSpeed);
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
      } 
      else if (IrReceiver.decodedIRData.command == 0x1) {
        analogWrite(ENA, maxSpeed);
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);
      }
      else if (IrReceiver.decodedIRData.command == 0x2) {
        analogWrite(ENA, maxSpeed);
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, LOW);
      }
    }
    IrReceiver.resume();
  }

}
