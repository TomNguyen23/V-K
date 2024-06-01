#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "lightSensor.h"

ESP8266WebServer server(80);

#define TENWIFI "Khong Co Nha"
#define PASSWIFI "7777@9999"

void connection() {
  String s = MAIN_page;
  server.send(200, "text/html", s);
}

void setup() {
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
  server.on("/readSerial", handleReadSerial);
  server.begin();
}

void handleReadSerial() {
  // Gửi giá trị cảm biến về client
  float light = analogRead(A0);
  server.send(200, "text/plain", "Giá trị cảm biến ánh sáng: " + String(light));
}

void loop() {
  // Xử lý các yêu cầu từ client
  server.handleClient();
}
