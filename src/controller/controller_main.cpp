#include <Bounce2.h>
#include "wireless.h"
#include "util.h"
#include "joystick.h"
#include "dpad.h"
#include "display.h"
#include "controller_pinout.h"

ControllerMessage prevControllerMessage;

Joystick joystick1(JOYSTICK1_X_PIN, JOYSTICK1_Y_PIN);
Joystick joystick2(JOYSTICK2_X_PIN, JOYSTICK2_Y_PIN);
DPad dPad;
Bounce2::Button buttonL;
Bounce2::Button buttonR;
Display display(TFT_CS_PIN, TFT_DC_PIN);

void setup() {
    Serial.begin(115200);

    setupWireless();

    joystick1.setup();
    joystick2.setup();
    dPad.setup();
    buttonL.attach(BUTTON_L_PIN, INPUT_PULLUP);
    buttonR.attach(BUTTON_R_PIN, INPUT_PULLUP);
    display.setup();

    Serial.println("Setup complete.");
}

void loop() {
    buttonL.update();
    buttonR.update();

    // Read and send controller sensors
    EVERY_N_MILLIS(50) {
        controllerMessage.millis = millis();
        controllerMessage.joystick1 = joystick1.read();
        controllerMessage.joystick2 = joystick2.read();
        controllerMessage.dPad = dPad.read();
        controllerMessage.buttonL = buttonL.read();
        controllerMessage.buttonR = buttonR.read();
        controllerMessage.touchPoint = display.read();
        
        if (!(prevControllerMessage == controllerMessage)) {
            // update display
            // display.clear();
            // display.drawControllerMessage(controllerMessage);
            sendControllerData();
            prevControllerMessage = controllerMessage;
        }
    }
}