#include <SoftwareSerial.h>
#include <Servo.h>

SoftwareSerial BTSerial(10, 11); // (Rx, Tx)
Servo myServo;

void setup() {
  myServo.attach(9);
  Serial.begin(9600);

  BTSerial.begin(9600);
}
void loop() {
  if (BTSerial.available()) {
    char data = BTSerial.read();
    Serial.println(data);

    if (data == '1') {
      myServo.write(180);
      delay(400);
      myServo.write(0);
    }
    else if (data == '0') {
      myServo.write(90);
      delay(400);
      myServo.write(0);
    }
    // else if (data == '2') {
    //   myServo.write(30);
    //   delay(500);
    //   myServo.write(0);
    // }
    // else if (data == '3') {
    //   myServo.write(60);
    //   delay(500);
    //   myServo.write(0);
    // }
    // else if (data == '4') {
    //   myServo.write(180);
    //   delay(500);
    //   myServo.write(90);
    // }

    // delay(100);
  }
}