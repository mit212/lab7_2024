#include "joystick.h"
#include "util.h"
#include <Arduino.h>

#define PRINT_DELAY 50

#define X_PIN A0
#define Y_PIN A1

Joystick joystick(X_PIN, Y_PIN);

void setup() {
    Serial.begin(115200);
    joystick.setup();
    Serial.println("Setup complete.");
}

void loop() {
    EVERY_N_MILLIS(PRINT_DELAY) {
        joystick.read(true);
    }
}
