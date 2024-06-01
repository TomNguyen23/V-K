#include <IRremote.hpp>
#include "DHT.h"         
 
const int DHTPIN = 5;       //Đọc dữ liệu từ DHT11 ở chân 2 trên mạch Arduino
const int DHTTYPE = DHT11;  //Khai báo loại cảm biến, có 2 loại là DHT11 và DHT22
DHT dht(DHTPIN, DHTTYPE);

int irPin = 3;
uint16_t address = 0x0;
uint16_t command;
uint16_t repeat = 0;

void setup() {
  IrSender.begin(irPin);
  IrSender.enableIROut(38);
  Serial.begin(9600);
  dht.begin();  
}

void loop() {
  float h = dht.readHumidity();    //Đọc độ ẩm
  float t = dht.readTemperature(); //Đọc nhiệt độ
  Serial.print("Nhiet do: ");
  Serial.println(t);               //Xuất nhiệt độ
  Serial.print("Do am: ");
  Serial.println(h);               //Xuất độ ẩm
  Serial.println();  

  if(t > 25 && h > 70) {
    command = 0x1;
  }
  else {
    command = 0x0;
  }

  Serial.println(command, HEX);
  IrSender.sendRC5(address, command, repeat, false);
  delay(1000);
}
