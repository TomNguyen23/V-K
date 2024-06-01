#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Servo.h>
#include "Servo.h"

Servo myservo;
ESP8266WebServer server(80);

#define TENWIFI "Khong Co Nha"
#define PASSWIFI "7777@9999"

void connection() {
  String s = MAIN_page;
  server.send(200, "text/html", s);
}

void setup() {
  myservo.attach(D1, 500,2400);
  Serial.begin(9600);

  WiFi.begin(TENWIFI, PASSWIFI);
  Serial.print("\n Đang thử kết nối");
  while (WiFi.status() != WL_CONNECTED) {
    delay (500); 
    Serial.print(".");
  }
  Serial.print("\n Kết nối thanh công. IP address: ");
  Serial.println(WiFi.localIP());
  server.begin(); // Khởi động server.
  Serial.print("Server đã khởi động.");

  server.on("/", connection);
  server.on("/sendValue", handleSendValue);
  server.begin();
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
  if (receivedValue > 0) {
      Serial.println(receivedValue);
      myservo.write(receivedValue);
      delay(500); 
      myservo.write(0);
      delay(500); 
  }
}