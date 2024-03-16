#include <Bounce2.h>
#include "wireless.h"
#include "util.h"
#include "joystick.h"
#include "dpad.h"
#include "display.h"
#include "controller_pinout.h"

ControllerMessage controllerMessage;
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

    // Read controller sensors
    EVERY_N_MILLIS(50) {
        controllerMessage.millis = millis();
        controllerMessage.joystick1 = joystick1.read();
        controllerMessage.joystick2 = joystick2.read();
        controllerMessage.dPad = dPad.read();
        controllerMessage.buttonL = buttonL.read();
        controllerMessage.buttonR = buttonR.read();
        controllerMessage.touchPoints = display.read();

        if (!(prevControllerMessage == controllerMessage)) {
            // update display
            display.clear();
            drawControllerMessage(controllerMessage);
            prevControllerMessage = controllerMessage;
        }
    }
}

void drawController() {
    // button L
    display.fillRect(0.1 * DISPLAY_WIDTH, 0.05 * DISPLAY_HEIGHT, 0.3 * DISPLAY_WIDTH, 0.1 * DISPLAY_HEIGHT, HX8357_WHITE);
    // button R 
    display.fillRect(0.6 * DISPLAY_WIDTH, 0.05 * DISPLAY_HEIGHT, 0.3 * DISPLAY_WIDTH, 0.1 * DISPLAY_HEIGHT, HX8357_WHITE);
    // joystick 1 
    display.fillRect(0.2 * DISPLAY_WIDTH - 0.175 * DISPLAY_HEIGHT, 0.25 * DISPLAY_HEIGHT, 
             0.35 * DISPLAY_HEIGHT, 0.35 * DISPLAY_HEIGHT, HX8357_WHITE);
    // joystick 2
    display.fillRect(0.8 * DISPLAY_WIDTH - 0.175 * DISPLAY_HEIGHT, 0.25 * DISPLAY_HEIGHT,
             0.35 * DISPLAY_HEIGHT, 0.35 * DISPLAY_HEIGHT, HX8357_WHITE);
    // rotary encoder
    display.fillCircle(0.5 * DISPLAY_WIDTH, 0.7 * DISPLAY_HEIGHT, 0.25 * DISPLAY_HEIGHT, HX8357_WHITE);
}

void drawControllerMessage(ControllerMessage message) {
    drawController();

    // button L
    if (controllerMessage.buttonL)
        display.fillRect(0.1 * DISPLAY_WIDTH, 0.05 * DISPLAY_HEIGHT, 0.3 * DISPLAY_WIDTH, 0.1 * DISPLAY_HEIGHT, HX8357_RED);
    // button R 
    if (controllerMessage.buttonR)
        display.fillRect(0.6 * DISPLAY_WIDTH, 0.05 * DISPLAY_HEIGHT, 0.3 * DISPLAY_WIDTH, 0.1 * DISPLAY_HEIGHT, HX8357_RED);
    // joystick 1 
    display.fillCircle(0.2 * DISPLAY_WIDTH + (-0.175 + controllerMessage.joystick1.x * 0.175)* DISPLAY_HEIGHT,
               (0.25 + controllerMessage.joystick1.y * 0.175) * DISPLAY_HEIGHT , 
               0.05 * DISPLAY_HEIGHT, HX8357_BLUE);
    // joystick 2
    display.fillCircle(0.8 * DISPLAY_WIDTH + (-0.175 + controllerMessage.joystick2.x * 0.175)* DISPLAY_HEIGHT,
               (0.25 + controllerMessage.joystick2.y * 0.175) * DISPLAY_HEIGHT , 
               0.05 * DISPLAY_HEIGHT, HX8357_BLUE);
    // rotary encoder
    if (controllerMessage.dPad.up)
        display.fillCircle(0.5 * DISPLAY_WIDTH, 0.5 * DISPLAY_HEIGHT, 0.05 * DISPLAY_HEIGHT, HX8357_RED);
    if (controllerMessage.dPad.down)
        display.fillCircle(0.5 * DISPLAY_WIDTH, 0.9 * DISPLAY_HEIGHT, 0.05 * DISPLAY_HEIGHT, HX8357_RED);    
    if (controllerMessage.dPad.left)
        display.fillCircle(0.5 * DISPLAY_WIDTH - 0.2 * DISPLAY_HEIGHT, 0.7 * DISPLAY_HEIGHT, 0.05 * DISPLAY_HEIGHT, HX8357_RED);     
    if (controllerMessage.dPad.right)
        display.fillCircle(0.5 * DISPLAY_WIDTH + 0.2 * DISPLAY_HEIGHT, 0.7 * DISPLAY_HEIGHT, 0.05 * DISPLAY_HEIGHT, HX8357_RED);  
    if (controllerMessage.dPad.select)
        display.fillCircle(0.5 * DISPLAY_WIDTH, 0.7 * DISPLAY_HEIGHT, 0.05 * DISPLAY_HEIGHT, HX8357_RED);   
    display.fillCircle(0.5 * DISPLAY_WIDTH + 0.2 * cos(controllerMessage.dPad.encoderPosition) * DISPLAY_HEIGHT, 
               (0.7 + 0.2 * sin(controllerMessage.dPad.encoderPosition)) * DISPLAY_HEIGHT,
               0.05 * DISPLAY_HEIGHT, HX8357_BLUE);
    // display touches
    display.drawTouches(0.025 * DISPLAY_HEIGHT, HX8357_GREEN);
}
