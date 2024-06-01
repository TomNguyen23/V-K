#include <IRremote.hpp>

int IR_SEND_PIN = 3;
int LIGHT = A0;

uint16_t address = 0x0;
uint16_t command;
uint16_t repeat = 0;

void setup() {
 IrSender.begin(IR_SEND_PIN);
 IrSender.enableIROut(38);
 Serial.begin(9600);
}

void loop() {
 int val = analogRead(LIGHT);
 Serial.print(val);
 Serial.print(" ");
 command = val > 150 ? 0x1 : 0x0;
 Serial.println(command, HEX);
 IrSender.sendRC5(address, command, repeat, false);
 delay(1000);
}

