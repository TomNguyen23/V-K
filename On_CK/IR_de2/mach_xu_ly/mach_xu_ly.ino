#include <Stepper.h>
#include <IRremote.hpp>

int LED1 = 2;
int LED2 = 3;
int LED3 = 4;
int BUZZER = 12;
int toneVal;
float sinVal;

const int irPin = 11;

const int stepsPerRevolution = 2048;
Stepper myStepper(stepsPerRevolution, 6, 8, 7, 9);

bool stepperDirection = true; // True = clockwise, False = counter-clockwise
bool objectNear = false;

void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  myStepper.setSpeed(14);
  
  IrReceiver.begin(irPin, ENABLE_LED_FEEDBACK); // Bắt đầu nhận tín hiệu IR
  Serial.begin(9600);
}

void loop() {
  if (IrReceiver.decode()) {
    unsigned long command = IrReceiver.decodedIRData.command;
    IrReceiver.resume(); // Chuẩn bị nhận tín hiệu tiếp theo

    Serial.println(command);
    if (command == 0x0) {
      stepperDirection = true;
      executeTasks();
    }
    else if (command == 0x1) {
      stepperDirection = false;
      executeTasks();
    }   
    else if (command == 0x2) {
      objectNear = true;
      digitalWrite(LED3, HIGH);
    } 
    else if (command == 0x3) {
      objectNear = false;
      digitalWrite(LED3, LOW);
      noTone(BUZZER);
    }

  }
}

void executeTasks() {
  if (objectNear) {
    BuzzerOn();
    blinkLEDs();
  }
  else {
    noTone(BUZZER);
    blinkLEDs();
    if (stepperDirection) {
      myStepper.step(stepsPerRevolution / 6); // 60 degrees clockwise
    } else {
      myStepper.step(-stepsPerRevolution / 6); // 60 degrees counter-clockwise
    }
  }
}

void BuzzerOn() {
  for (int x = 0; x < 180; x++) {
    sinVal = (sin(x * 3.1415 / 180));
    toneVal = 2000 + (int(sinVal * 1000));
    tone(BUZZER, toneVal);
    delay(2);
  }
}

void blinkLEDs() {
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, LOW);
  delay(250);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, HIGH);
  delay(250);
}
