const int trigPin = 5;
const int echoPin = 3;
long duration;
int distance;
int Speaker = 6;
int toneVal;
float sinVal;

void setup() {
  pinMode(Speaker, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);

}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  distance = duration * 0.034 / 2;

  if (distance >= 10 && distance <= 20) {
    for (int x = 0; x < 180; x++) {
      sinVal = (sin(x * 3.1415 / 180));
      toneVal = 2000 + (int(sinVal * 1000));
      tone(Speaker, toneVal);
      delay(2);
    }
  } else {
    noTone(Speaker);
  }

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println("cm");

}

