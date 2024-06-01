#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "LEDstatus.h"


#define TENWIFI "POCO X3 Pro"
#define PASSWIFI "11111111"
ESP8266WebServer server(80);

int led_status = 1;
int LED = D1;

void connection() {
  String s = MAIN_page;
  server.send(200, "text/html", s);
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

void setup(){
  pinMode(LED, OUTPUT);
  digitalWrite(LED, HIGH);

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
  server.on("/LEDstatus", handleLED);
  server.begin();
}

void loop() {
  server.handleClient();
}
