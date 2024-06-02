#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Stepper.h>
#include <String.h>
#include "LineSensor_Stepper.h"

const int stepperRevolution = 2048;
Stepper myStepper(stepperRevolution, D1, D3, D2, D4);
ESP8266WebServer server(80);
int linePin = D5;

#define TENWIFI "POCO X3 Pro"
#define PASSWIFI "11111111"

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
  server.on("/readSerial", handleReadSerial);
  server.on("/sendValue", handleSendValue);
  server.begin();
}

void handleReadSerial() {
  // Gửi giá trị cảm biến về client
    int val = digitalRead(linePin);
    server.send(200, "text/plain", "Giá trị cảm biến dò line: " + String(val));
}

int receivedValue = 0;
void handleSendValue() {
  if (server.hasArg("degrees")) {
    String recString = server.arg("degrees");
    bool isNeg = (recString[0] == '-') ? true : false;
    if (isNeg) {
      recString[0] = '0';
      receivedValue = -1.0 * recString.toInt();
    } else {
      receivedValue = server.arg("degrees").toInt();
    }
  }
}

bool isStepped = false;
int offset = 0;

void loop() {
  server.handleClient();

  unsigned long currentMillis = millis();  

  if (receivedValue != 0 && currentMillis % 500 <= 15 && !isStepped) {
    int degree = receivedValue;
    if (receivedValue < 0) {
      degree = receivedValue - offset;
    }
    else {
      degree = receivedValue + offset;
    }
    Serial.println(degree);
    myStepper.step(degreeToSteps(degree));
    isStepped = true;
  } else {
    isStepped = false;
  }
}