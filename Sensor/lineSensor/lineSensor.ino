int line = 5;
int val;

void setup() {
  Serial.begin(9600);

}

void loop() {
  val = digitalRead(line);
  Serial.println(val);
  delay(500);

}
