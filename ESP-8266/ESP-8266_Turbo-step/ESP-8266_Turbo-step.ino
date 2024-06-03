#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Stepper.h>
#include <String.h>
#include "TurboSensor_Stepper.h"

const int stepperRevolution = 2048;
Stepper myStepper(stepperRevolution, D1, D3, D2, D4);
ESP8266WebServer server(80);
int trigPin = D5;
int echoPin = D6;
float duration;
float distance;

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
  pinMode(trigPin, OUTPUT);
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
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    duration = pulseIn(echoPin, HIGH);

    distance = duration * 0.034 / 2; 
    
    Serial.print("distance: ");
    Serial.println(distance);
    server.send(200, "text/plain", "Giá trị cảm biến khoảng cách: " + String(distance) + " cm");
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
bool isSpined = false;
bool isStoped = false;

void loop() {
  // Xử lý các yêu cầu từ client
  server.handleClient();
  // if (receivedValue != 0) {
  //   Serial.println(receivedValue);
  //   myStepper.step(degreeToSteps(receivedValue));
  //   delay(200);
  //   myStepper.step(degreeToSteps(0));
  //   delay(200);
  // }
    unsigned long currentMillis = millis();  

    if (receivedValue != 0 && currentMillis % 500 <= 15 && !isSpined) {
      if (isStoped) {
        myStepper.step(degreeToSteps(0));
        isStoped = false;
      } else {
        myStepper.step(degreeToSteps(receivedValue));
        isStoped = true;
      }
      // myStepper.step(degreeToSteps(receivedValue));
      // delay(800);
      // myStepper.step(degreeToSteps(0));
      // delay(800);
      isSpined = true;
    } else {
      isSpined = false;
    }

}