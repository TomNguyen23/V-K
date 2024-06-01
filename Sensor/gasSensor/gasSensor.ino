int const PINO_SGAS = A0;
int Speaker = 11;
int toneVal;
float sinVal;

void setup() {
  pinMode(Speaker, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int val = analogRead(PINO_SGAS);
  Serial.println(val, DEC);
  delay(200);

  if (val >= 300) {
    for (int x = 0; x < 180; x++) {
      sinVal = (sin(x * 3.1415 / 180));
      toneVal = 2000 + (int(sinVal * 1000));
      tone(Speaker, toneVal);
      delay(2);
    }
  } else {
    noTone(Speaker);
  }

}
