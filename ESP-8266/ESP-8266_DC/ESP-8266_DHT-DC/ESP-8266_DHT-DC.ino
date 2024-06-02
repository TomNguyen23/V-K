#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "DHT.h"
#include "DHT_DC.h"

ESP8266WebServer server(80);

const int DHTPIN = D5;
const int DHTTYPE = DHT11;
DHT dht(DHTPIN, DHTTYPE);

#define maxSpeed  255
#define minSpeed  0
int step = 10;
int ENA = D1;
int IN1 = D2;
int IN2 = D3;

#define TENWIFI "Huu Chin"
#define PASSWIFI "9999@9999"

void connection() {
  String s = MAIN_page;
  server.send(200, "text/html", s);
}

void setup() {
  Serial.begin(9600);
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

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
  server.on("/DCforward", handleDCforward);
  server.on("/DCbackward", handleDCbackward);
  server.on("/DCspeedup", handleDCspeedUp);
  server.on("/DCspeeddown", handleDCspeedDown);
  server.begin();
}

// ---------handle action------------------
void handleReadSerial() {
  // Gửi giá trị cảm biến về client
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  server.send(200, "text/plain", "Giá trị cảm biến DHT: " + String(h) + "% | " + String(t) + " độ C");
}

bool DCdirection = true;  //true: go forward
void handleDCforward() {
  DCdirection = true;
  server.send(200, "text/plain", "go forward");
}

void handleDCbackward() {
  DCdirection = false;
  server.send(200, "text/plain", "go backward");
}


bool DCspeed = true;  //true: speed up
void handleDCspeedUp() {
  DCspeed = true;
  server.send(200, "text/plain", "speedUp");
}

void handleDCspeedDown() {
  DCspeed = false;
  server.send(200, "text/plain", "speedDown");
}
// ----------------------------------------------


// -----------------action----------------------
void DCmove_forward() {
  analogWrite(ENA, maxSpeed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
}

void DCmove_backward() {
  analogWrite(ENA, maxSpeed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
}

void DCspeedUp() {
  for (int i = 10; i <= maxSpeed; i += step) {
    analogWrite(ENA, i);
  }
}

void DCspeedDown() {
  for (int i = maxSpeed; i >= 10; i -= step) {
    analogWrite(ENA, i);
  }
}
// ----------------------------------------------

void loop() {
  // Xử lý các yêu cầu từ client
  server.handleClient();
  
  if (DCdirection) DCmove_forward();
  else DCmove_backward();

  if (DCspeed) DCspeedUp();
  else DCspeedDown();
}