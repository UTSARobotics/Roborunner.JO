#include <SoftwareSerial.h>

// Bluetooth on pins 6 (RX) and 5 (TX)
SoftwareSerial BT(6, 5);

// Motor A pins
#define PWMA 3
#define DIRA 12
#define DIRB 13

// Motor B pins
#define PWMB 11
#define BRAKE_B1 8
#define BRAKE_B2 9

void setup() {
  Serial.begin(9600);
  BT.begin(9600);

  // Motor A pins
  pinMode(PWMA, OUTPUT);
  pinMode(DIRA, OUTPUT);
  pinMode(DIRB, OUTPUT);

  // Motor B pins
  pinMode(PWMB, OUTPUT);
  pinMode(BRAKE_B1, OUTPUT);
  pinMode(BRAKE_B2, OUTPUT);

  // Release brake and stop motors
  digitalWrite(BRAKE_B1, LOW);
  digitalWrite(BRAKE_B2, LOW);
  analogWrite(PWMA, 0);
  analogWrite(PWMB, 0);

  Serial.println("RECEIVER ACTIVE - Two Motors Ready");
}

void loop() {
  if (BT.available()) {
    char cmd = BT.read();
    Serial.print("Received: ");
    Serial.println(cmd);

    switch (cmd) {
      case 'F':
        // Forward
        digitalWrite(DIRA, HIGH);   // Motor A forward
        digitalWrite(DIRB, LOW);    // Motor A back dir pin
        analogWrite(PWMA, 200);

        analogWrite(PWMB, 200);     // Motor B forward
        Serial.println("Motors: FORWARD");
        break;

      case 'B':
        // Backward
        digitalWrite(DIRA, LOW);    // Motor A backward
        digitalWrite(DIRB, HIGH);
        analogWrite(PWMA, 200);

        analogWrite(PWMB, 200);     // Motor B backward
        Serial.println("Motors: BACKWARD");
        break;

      case 'L':
        // Left turn: Motor A back, Motor B forward
        digitalWrite(DIRA, LOW);    // Motor A backward
        digitalWrite(DIRB, LOW);
        analogWrite(PWMA, 200);

        analogWrite(PWMB, 200);     // Motor B forward
        Serial.println("Motors: LEFT");
        break;

      case 'R':
        // Right turn: Motor A forward, Motor B back
        digitalWrite(DIRA, HIGH);   // Motor A forward
        digitalWrite(DIRB, HIGH);
        analogWrite(PWMA, 200);

        analogWrite(PWMB, 200);     // Motor B backward
        Serial.println("Motors: RIGHT");
        break;

      case 'S':
        // Stop
        analogWrite(PWMA, 0);
        analogWrite(PWMB, 0);
        Serial.println("Motors: STOPPED");
        break;
    }
  }
}
