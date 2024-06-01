#include <SoftwareSerial.h>
#include "DHT.h"

SoftwareSerial BTSerial(10, 11); // (Rx, Tx)

const int DHTPIN = 5; 
const int DHTTYPE = DHT11;
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();  
  Serial.println("Master is ready!");
  BTSerial.begin(9600);
}
void loop() {
  float h = dht.readHumidity();    //Đọc độ ẩm
  float t = dht.readTemperature(); //Đọc nhiệt độ
  Serial.print("Nhiet do: ");
  Serial.println(t);               //Xuất nhiệt độ
  Serial.print("Do am: ");
  Serial.println(h);               //Xuất độ ẩm
  Serial.println();

  if(t > 25 && h > 76) BTSerial.write("1");
  else BTSerial.write("0");

  delay(1000);
}