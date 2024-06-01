#include "DHT.h"    
#include <OneWire.h>        

const int DHTPIN = 4;       //Đọc dữ liệu từ DHT11 ở chân 2 trên mạch Arduino
const int DHTTYPE = DHT11;  //Khai báo loại cảm biến, có 2 loại là DHT11 và DHT22

const int alarm = 12;
float sinVal;
int toneVal;

OneWire ds(DHTPIN); 
DHT dht(DHTPIN, DHTTYPE);
 
void setup() {
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
  
  Serial.println();                //Xuống hàng
  delay(1000);                     //Đợi 1 giây
  if (t > 30 && h > 80){
    for (int x = 0; x < 180 ; x++){
      sinVal = sin(x * (3.1412 / 180));
      toneVal = 2000 + (int(sinVal * 1000));
      tone(alarm, toneVal);
      delay(2);
    }
  }
  else noTone(alarm);
  
}
