#include <SoftwareSerial.h>

SoftwareSerial BTSerial(10, 11); // (Rx, Tx)
int Joystick_x = A0;
int Joystick_y = A1;
int Joystick_sw = 2;

void setup() {
  Serial.begin(9600);
  BTSerial.begin(9600);
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

  if (y > 1000){
    BTSerial.write("0");
  }
  else if (y < 100) {
    BTSerial.write("1");
  }
  else if (x > 1000) {
    BTSerial.write("2");
  }
  else if (x < 100) {
    BTSerial.write("3");
  }
  else if (sw == 0) {
    BTSerial.write("4");
  }

  delay(500);
}
