#define maxSpeed  255
#define minSpeed  0
int step = 10;
int ENA = 3;
int ENB = 9;
int IN1 = 4;
int IN2 = 5;
int IN3 = 6;
int IN4 = 7;

const int trigPin = 9;
const int echoPin = 10;
long duration;
int distance;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void DCstop() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  // digitalWrite(IN3, LOW);
  // digitalWrite(IN4, LOW);
}

void DCmove_forward() {
  // analogWrite(ENB, maxSpeed);
  analogWrite(ENA, maxSpeed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  // digitalWrite(IN3, HIGH);
  // digitalWrite(IN4, LOW);
}

void DCmove_backward() {
  // analogWrite(ENB, maxSpeed);
  analogWrite(ENA, maxSpeed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  // digitalWrite(IN3, LOW);
  // digitalWrite(IN4, HIGH);
}

void DCspeedUp() {
  for (int i = 0; i <= maxSpeed; i+= step) {
    analogWrite(ENA, i);
    delay(20);
  }
}

void DCspeedDown() {
  for (int i = maxSpeed; i >= 0; i-= step) {
    analogWrite(ENA, i);
    delay(20);
  }
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  distance = duration * 0.034 / 2;

  if(distance < 10) DCstop();
  if(distance > 10 && distance < 30) DCmove_forward();
  if(distance > 30) DCmove_backward();

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println("cm");

}
