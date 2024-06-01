#include <Servo.h>

Servo myServo;
const int SERVO_PIN = 9;
int Joystick_x = A0;
int Joystick_y = A1;
int Joystick_sw = 2;


void setup() {
  myServo.attach(SERVO_PIN);
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

  if (y > 1000){
    myServo.write(0);
  }
  if (y < 100) {
    myServo.write(180);
  }
  if (x > 1000) {
    myServo.write(120);
  }
  if (x < 100) {
    myServo.write(60);
  }
  if (sw == 0) {
    myServo.write(90);
  }

  delay(200);

}


