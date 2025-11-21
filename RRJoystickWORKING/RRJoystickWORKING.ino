#include <SoftwareSerial.h>

SoftwareSerial BT(6, 5);  // HC-05 TX→6, RX→5

#define JOY_X A0
#define JOY_Y A1

// Neutral zone for your joystick
#define NEUTRAL_MIN 300
#define NEUTRAL_MAX 360

char lastCommand = 'S';  // Start with STOP so robot doesn’t move on boot

void setup() {
  Serial.begin(9600);
  BT.begin(9600);

  Serial.println("Joystick Controller Active (No-Spam Mode)");
}

void loop() {
  int x = analogRead(JOY_X);
  int y = analogRead(JOY_Y);

  char command = 'S';  // Default → STOP

  // --- PRIORITY: Y axis first ---
  if (y > 600) {
    command = 'F';          // Forward
  } else if (y < 100) {
    command = 'B';          // Backward
  }
  // If Y is neutral, check X
  else if (x > 600) {
    command = 'R';          // Right
  } else if (x < 100) {
    command = 'L';          // Left
  } else {
    command = 'S';          // Neutral stop
  }

  // --- SEND ONLY IF COMMAND CHANGED ---
  if (command != lastCommand) {
    BT.write(command);          // send to robot
    lastCommand = command;      // update tracker

    // Print status
    Serial.print("X: ");
    Serial.print(x);
    Serial.print("  Y: ");
    Serial.print(y);
    Serial.print("  → SENT: ");
    Serial.println(command);
  }

  delay(50);  // small delay to stabilize readings
}
