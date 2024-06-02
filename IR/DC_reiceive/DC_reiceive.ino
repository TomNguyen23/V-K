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

void DCmove_forward() {
  analogWrite(ENA, maxSpeed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
}

void DCmove_backward() {
  analogWrite(ENA, maxSpeed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
}

void DCspeedUp() {
  for (int i = 10; i <= maxSpeed; i += step) {
    analogWrite(ENA, i);
  }
}

void DCspeedDown() {
  for (int i = maxSpeed; i >= 10; i -= step) {
    analogWrite(ENA, i);
  }
}

void loop() {
  if (IrReceiver.decode()) {
    if (IrReceiver.decodedIRData.protocol == UNKNOWN) {
      Serial.println(("Unknown"));
    } else {
      IrReceiver.printIRResultShort(&Serial);
      IrReceiver.printIRSendUsage(&Serial);
      if (IrReceiver.decodedIRData.command == 0x0) {
        DCmove_forward();
      } 
      else if (IrReceiver.decodedIRData.command == 0x1) {
        DCmove_backward();
      }
      else if (IrReceiver.decodedIRData.command == 0x2) {
        analogWrite(ENA, maxSpeed);
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, LOW);
      }
      else if (IrReceiver.decodedIRData.command == 0x3) {
        DCspeedUp();
      }
      else if (IrReceiver.decodedIRData.command == 0x4) {
        DCspeedDown();
      }
    }
    IrReceiver.resume();
  }

}
