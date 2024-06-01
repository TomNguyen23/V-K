#include <Servo.h>

Servo myServo;
const int SERVO_PIN = 9;
int const PINO_SGAS = A0;

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
    int val = analogRead(PINO_SGAS);
    Serial.println(val, DEC);

    if(val > 450) myServo.write(180);
    else myServo.write(60);
  }

  delay(800);

}
