#include <Stepper.h>
#include "DHT.h"

const int stepPerRevolution = 2048;
Stepper myStepper(stepPerRevolution, 8, 10, 9, 11);

const int DHTPIN = 13;       //Đọc dữ liệu từ DHT11 ở chân 2 trên mạch Arduino
const int DHTTYPE = DHT11;  //Khai báo loại cảm biến, có 2 loại là DHT11 và DHT22
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  myStepper.setSpeed(14);
  Serial.begin(9600);
  dht.begin();  
}

int degreeToSteps(int degree) {
  if (degree == 0) return 0;
  return stepPerRevolution / (360 / degree);
}

void loop() {
  float h = dht.readHumidity();    //Đọc độ ẩm
  float t = dht.readTemperature(); //Đọc nhiệt độ
  Serial.print("Nhiet do: ");
  Serial.println(t);               //Xuất nhiệt độ
  Serial.print("Do am: ");
  Serial.println(h);               //Xuất độ ẩm
  Serial.println();                //Xuống hàng

  if (t > 25 && h > 76){
    myStepper.step(degreeToSteps(60));
  }
  else {
    myStepper.step(-degreeToSteps(90));
  }
  delay(100);                     
}
