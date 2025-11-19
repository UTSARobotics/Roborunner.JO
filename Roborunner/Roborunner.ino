// TEST IF IR RECEIVER WORKS ON PIN 3
#include <IRremote.hpp>

void setup() {
    Serial.begin(9600);
    while (!Serial);
    delay(1000);
    
    Serial.println("=== IR RECEIVER TEST - PIN 3 ===");
    
    // Check pin state first
    pinMode(3, INPUT);
    Serial.print("Pin 3 initial state: ");
    Serial.println(digitalRead(3));
    
    // Initialize IR
    IrReceiver.begin(3, ENABLE_LED_FEEDBACK);
    Serial.println("IR receiver started on pin 3");
    Serial.println("Press remote buttons now!");
    Serial.println("");
}

void loop() {
    // Check for IR signals
    if (IrReceiver.decode()) {
        Serial.println("*** IR DETECTED ***");
        Serial.print("Code: 0x");
        Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);
        Serial.print("Protocol: ");
        Serial.println(IrReceiver.decodedIRData.protocol);
        Serial.println("");
        
        IrReceiver.resume();
    }
    
    // Also monitor raw pin changes
    static int lastState = -1;
    static unsigned long lastPrint = 0;
    int currentState = digitalRead(3);
    
    if (currentState != lastState) {
        Serial.print("Pin 3 changed to: ");
        Serial.println(currentState);
        lastState = currentState;
    }
    
    if (millis() - lastPrint > 3000) {
        Serial.print("Monitoring... Pin 3: ");
        Serial.println(currentState);
        lastPrint = millis();
    }
    
    delay(10);
}