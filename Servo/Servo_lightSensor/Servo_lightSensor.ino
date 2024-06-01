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
  if(state == 0) {
    state = 1;
    myServo.write(0);
  }
  else {
    state = 0;
    int lightVal = analogRead(POT_PIN);
    Serial.println(lightVal);
    if(lightVal > 600) myServo.write(110);
    else myServo.write(180);
  }


  delay(800);

}
