#include <IRremote.hpp>

int irPin = 3;
int linePin = 5;
uint16_t address = 0x0;
uint16_t command;
uint16_t repeat = 0;

void setup() {
  Serial.begin(9600);
  IrSender.begin(irPin);
  IrSender.enableIROut(38);
}

void loop() {
  int val = digitalRead(linePin);
  Serial.println(val);

  command = val == 0 ? 0x1 : 0x0;
  Serial.println(command, HEX);
  IrSender.sendRC5(address, command, repeat, false);
  delay(1000);
}
