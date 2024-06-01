#include <Servo.h>


Servo myServo;
const int SERVO_PIN = 9;
const int LINE_PIN = 5;
int state = 0;

void setup() {
  myServo.attach(SERVO_PIN);
  Serial.begin(9600);
}

void loop() {  
  if(state == 0) {
    state = 1;
    myServo.write(0);
  }
  else {
    state = 0;
    int lineVal = digitalRead(LINE_PIN);
    Serial.println(lineVal);
    if(lineVal == 0) myServo.write(110);
    else myServo.write(180);
  }


  delay(800);

}
