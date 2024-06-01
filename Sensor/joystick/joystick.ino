int Joystick_x = A1;
int Joystick_y = A3;
int Joystick_sw = 2;


void setup() {
  pinMode(Joystick_sw, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  int x, y, sw;
  x = analogRead(Joystick_x);
  y = analogRead(Joystick_y);
  sw = digitalRead(Joystick_sw);

  Serial.print("x = ");
  Serial.print(x);
  Serial.print("\t\t y = ");
  Serial.print(y);
  Serial.print("\t\t sw = ");
  Serial.println(sw);

  delay(1000);
}
