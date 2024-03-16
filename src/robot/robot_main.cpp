#include <Arduino.h>
#include "util.h"
#include "wireless.h"
#include "robot_drive.h"

void setup() {
    Serial.begin(115200);
    setupDrive();
    setupWireless();
}

double forward = 0;
double turn = 0;

void loop() {

    // Update setpoint at 2kHz
    // Update setpoint at 50Hz
    EVERY_N_MILLIS(20) {
        if (freshWirelessData) {
            forward = mapDouble(controllerMessage.joystick1.x, 0.0, 4096.0, -MAX_FORWARD, MAX_FORWARD);
            turn = mapDouble(controllerMessage.joystick1.y, 0.0, 4096.0, -MAX_TURN, MAX_TURN);
            updateSetpoints(forward, turn);
        }
        // Serial.printf("Forward: %.2f, Turn: %.2f \n",
        //             forward, turn);
    }

    //update PID at 5kHz
    //update PID at 200Hz
    EVERY_N_MILLIS(5) {
        updatePIDs();
    }

    // // Print values at 20Hz
    // EVERY_N_MILLIS(50) {
    //     Serial.printf("Forward: %.2f, Turn: %.2f \n",
    //                 forward, turn);
    // }

    // Send robot values at 20Hz
    EVERY_N_MILLIS(50) {
        sendRobotData();
    }
  
}