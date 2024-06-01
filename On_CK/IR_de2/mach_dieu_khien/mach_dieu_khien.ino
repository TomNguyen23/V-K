#include <IRremote.hpp>  

const int trigPin = 5;
const int echoPin = 4;
long duration;
int distance;

int irPin = 9;
uint16_t address = 0x0;
uint16_t repeat = 0;

// Khai báo nút bấm
int buttonA = 2;
int buttonB = 3;

void setup() {
  Serial.begin(9600);
  IrSender.begin(irPin);
  IrSender.enableIROut(38);

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
    IrSender.sendRC5(address, 0x0, repeat, false);
    delay(500);
  }
  else if (buttonStateA == HIGH && buttonStateB == HIGH) {
    IrSender.sendRC5(address, 0x1, repeat, false);
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
    IrSender.sendRC5(address, 0x2, repeat, false);
  } else {
    IrSender.sendRC5(address, 0x3, repeat, false);
  }
  delay(500);
}
