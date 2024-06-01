#include <Servo.h>


Servo myServo;
const int SERVO_PIN = 9;
const int POT_PIN = A0;
int state = 0;

void setup() {
  myServo.attach(SERVO_PIN);
  Serial.begin(9600);
}

void loop() {  
  int val = analogRead(POT_PIN);
    int angle = map(val, 0, 1023, 0, 180);
    myServo.write(angle);
    delay(2);

}
