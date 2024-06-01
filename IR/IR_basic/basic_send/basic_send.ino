#include <IRremote.hpp>
int IR_SEND_PIN = 3;
int LIGHT = 0;

uint16_t address = 0x0;
uint16_t repeat = 0;

void setup() {
 IrSender.begin(IR_SEND_PIN);
 IrSender.enableIROut(38);
 Serial.begin(9600);
}

void loop() {
 IrSender.sendRC5(address, 0x0, repeat);
 delay(1000);
 IrSender.sendRC5(address, 0x1, repeat);
 delay(1000);
}

