#define maxSpeed  255
#define minSpeed  0
int step = 10;
int ENA = 3;
int ENB = 9;
int IN1 = 4;
int IN2 = 5;
int IN3 = 6;
int IN4 = 7;

int button = 2;
int x, y;

void setup() {
  Serial.begin(9600);
  pinMode(button, INPUT_PULLUP);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void DCstop() {
  // digitalWrite(IN1, LOW);
  // digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

// void DCmove_forward(int signal) {
//   int value = map(signal, 0, 1023, 0, 255);
//   analogWrite(ENA, value);
//   analogWrite(ENB, value);

//   if(signal > 540) {
    
//     digitalWrite(IN1, HIGH);
//     digitalWrite(IN2, LOW);
//     digitalWrite(IN3, HIGH);
//     digitalWrite(IN4, LOW);
//   } 
//   if(signal < 500) {
//     digitalWrite(IN1, LOW);
//     digitalWrite(IN2, HIGH);
//     digitalWrite(IN3, LOW);
//     digitalWrite(IN4, HIGH);
//   }
// }

// void DCmove_backward(int signal) {
//   int value = map(signal, 0, 1023, 0, 255);
//   analogWrite(ENA, value);
//   analogWrite(ENB, value);
//   digitalWrite(IN1, LOW);
//   digitalWrite(IN2, HIGH);
//   digitalWrite(IN3, LOW);
//   digitalWrite(IN4, HIGH);
// }

void DCmove_forward() {
  analogWrite(ENB, maxSpeed);
  // analogWrite(ENA, maxSpeed);
  // digitalWrite(IN1, HIGH);
  // digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void DCmove_backward() {
  analogWrite(ENB, maxSpeed);
  // analogWrite(ENA, maxSpeed);
  // digitalWrite(IN1, LOW);
  // digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void DCspeedUp() {
  for (int i = 0; i <= maxSpeed; i+= step) {
    analogWrite(ENB, i);
    //delay(20);
  }
}

void DCspeedDown() {
  for (int i = maxSpeed; i >= 0; i-= step) {
    analogWrite(ENB, i);
    //delay(20);
  }
}

void loop() {
  int sw = digitalRead(button);
  x = analogRead(A0);
  y = analogRead(A1);
  Serial.print("x = ");
  Serial.print(x);
  Serial.print("\t\t y = ");
  Serial.print(y);
  Serial.print("\t\t sw = ");
  Serial.println(sw);

  if(y > 1000) {
    DCmove_forward();
  }
  if(y < 100) {
    DCmove_backward();
  }

  if (x > 1000) {
    DCspeedUp();
  }

  if (x < 100) {
    DCspeedDown();
  }
  delay(100);
}
