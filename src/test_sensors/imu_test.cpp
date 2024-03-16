#include "util.h"
#include "imu.h"

#define PRINT_DELAY 50

#define BNO08X_CS 12
#define BNO08X_INT 13
#define BNO08X_RESET 14

IMU imu(BNO08X_RESET, BNO08X_CS, BNO08X_INT);
EulerAngles imuAngles;

void setup() {
    Serial.begin(115200);
    imu.setup();
    Serial.println("Setup complete.");
}

void loop() {
    imu.update();

    EVERY_N_MILLIS(PRINT_DELAY) {
        imuAngles = imu.getEulerAngles();

        Serial.printf("RPY (rad): %.2f   %.2f   %.2f\n", 
                      imuAngles.roll, imuAngles.pitch, imuAngles.yaw);
    }
}

