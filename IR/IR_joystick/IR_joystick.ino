#include <IRremote.h>  
 
int Joystick_x = A0;
int Joystick_y = A1;
int Joystick_sw = 2;

int irPin = 3;
IRsend irsend(irPin);

void setup() {
  Serial.begin(9600);
  pinMode(Joystick_sw, INPUT_PULLUP);
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
  
  unsigned long tData;

  if(distance >= 10 && distance <= 20) {
    tData = 0x1;
  }
  else {
    tData = 0x0;
  }

  irsend.sendRC5(tData, 16);
  delay(50);
}
