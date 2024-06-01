#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Stepper.h>
#include "Sensor_motor.h"
#include "DHT.h"
// #include <String.h>

const int stepperRevolution = 2048;
Stepper myStepper(stepperRevolution, D1, D3, D2, D4);
ESP8266WebServer server(80);

const int DHTPIN = D5;
const int DHTTYPE = DHT11;
DHT dht(DHTPIN, DHTTYPE);


int led_status = 1;
int LED = D7;

#define TENWIFI "Huu Chin"
#define PASSWIFI "9999@9999"

int degreeToSteps(int degree) {
  if (degree == 0) return 0;
  return stepperRevolution / (360 / degree);
}

void connection() {
  String s = MAIN_page;
  server.send(200, "text/html", s);
}

void setup() {
  myStepper.setSpeed(14);
  Serial.begin(9600);

  pinMode(LED, OUTPUT);
  digitalWrite(LED, HIGH);


  WiFi.begin(TENWIFI, PASSWIFI);
  Serial.print("\n Đang thử kết nối");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("\n Kết nối thanh công. IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();  // Khởi động server.
  Serial.print("Server đã khởi động.");

  server.on("/", connection);
  server.on("/readDHT11", handleReadDHT11);
  server.on("/readLight", handleReadLight);
  server.on("/sendValue", handleSendValue);
  server.on("/LEDstatus", handleLED);
  server.begin();
}

void handleReadDHT11() {
  // Gửi giá trị cảm biến về client
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  server.send(200, "text/plain", "Giá trị cảm biến DHT: " + String(h) + "% | " + String(t) + " độ C");
}

void handleReadLight() {
  // Gửi giá trị cảm biến về client
  int lightVal = analogRead(A0);

  if (lightVal < 100) {
    server.send(200, "text/plain", "Hiện giờ trời đang sáng, giá trị: " + String(lightVal));
  } 
  else {
    server.send(200, "text/plain", "Hiện giờ trời đang tối, giá trị: "  + String(lightVal));
  }
}

void handleLED(){
  if (led_status == 1){
    digitalWrite(LED, LOW);
    server.send(200, "text/plain", "0");
    led_status = 0;
  } else if (led_status == 0){
    digitalWrite(LED, HIGH);
    server.send(200, "text/plain", "1");
    led_status = 1;
  }
}

int receivedValue = 0;
void handleSendValue() {
  if (server.hasArg("degrees")) {
    receivedValue = server.arg("degrees").toInt();
  }
}

void loop() {
  // Xử lý các yêu cầu từ client
  server.handleClient();
  if (receivedValue != 0) {
    // Serial.println(receivedValue);
    myStepper.step(degreeToSteps(receivedValue));
    delay(200);
    // receivedValue = 0;
  }
}