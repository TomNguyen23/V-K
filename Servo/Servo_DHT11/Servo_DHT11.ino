#include <Servo.h>
#include "DHT.h"

Servo myServo;
const int SERVO_PIN = 9;
const int DHTPIN = 5; 
const int DHTTYPE = DHT11;
DHT dht(DHTPIN, DHTTYPE);

int state = 0;

void setup() {
  myServo.attach(SERVO_PIN);
  dht.begin();  
  Serial.begin(9600);
}

void loop() {  
  if(state == 0) {
    state = 1;
    myServo.write(0);
  }
  else {
    state = 0;
    float h = dht.readHumidity();    //Đọc độ ẩm
    float t = dht.readTemperature(); //Đọc nhiệt độ
    Serial.print("Nhiet do: ");
    Serial.println(t);               //Xuất nhiệt độ
    Serial.print("Do am: ");
    Serial.println(h);               //Xuất độ ẩm
    Serial.println();  

    if(t > 25 && h > 76) myServo.write(110);
    else myServo.write(180);
  }

  delay(800);

}
