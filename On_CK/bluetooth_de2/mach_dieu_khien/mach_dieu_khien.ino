#include <SoftwareSerial.h>

SoftwareSerial BTSerial(10, 11); // (Rx, Tx)
const int trigPin = 5;
const int echoPin = 4;
long duration;
int distance;

// Khai báo nút bấm
int buttonA = 2;
int buttonB = 3;

void setup() {
  Serial.begin(9600);
  BTSerial.begin(9600);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  // Khởi tạo nút bấm
  pinMode(buttonA, INPUT_PULLUP);
  pinMode(buttonB, INPUT_PULLUP);
}

void loop() {
  // Đọc trạng thái nút bấm
  int buttonStateA = digitalRead(buttonA);
  // int buttonStateB = digitalRead(buttonB);

  int buttonStateB = LOW;

  Serial.print("button A: ");
  Serial.println(buttonStateA);
  // Serial.print("button b: ");
  // Serial.println(buttonStateB);

  
  // Kiểm tra nút bấm A
  if (buttonStateA == HIGH && buttonStateB == LOW) {
    BTSerial.println("A");
    delay(500);
  }
  else if (buttonStateA == HIGH && buttonStateB == HIGH) {
    BTSerial.println("AandB");
    delay(500);
  }
  
  // Đọc khoảng cách từ cảm biến siêu âm
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  distance = duration * 0.034 / 2;
  Serial.print("distance: ");
  Serial.println(distance);


  if (distance <= 15) {
    BTSerial.println("OBJECT_NEAR");
  } else {
    BTSerial.println("OBJECT_FAR");
  }
  delay(500);
}
