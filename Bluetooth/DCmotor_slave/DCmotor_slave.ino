#include <SoftwareSerial.h>

SoftwareSerial BTSerial(10, 11); // (Rx, Tx)

#define maxSpeed  255
#define minSpeed  0
int step = 10;
int ENA = 3;
int IN1 = 4;
int IN2 = 5;

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  Serial.begin(9600);
  BTSerial.begin(9600);
}

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

void loop() {
  if (BTSerial.available()) {
    char data = BTSerial.read();
    Serial.println(data);

    if (data == '1') {
      DCmove_backward();

    }
    else if (data == '0') {
      DCmove_forward();
    }
    else if (data == '2') {
      DCspeedUp();
    }
    else if (data == '3') {
      DCspeedDown();
    }
    else if (data == '4') {
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);    
    }
  }

}
