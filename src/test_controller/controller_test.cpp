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
// DPad dPad;
Bounce2::Button buttonL;
Bounce2::Button buttonR;
Display display(TFT_CS_PIN, TFT_DC_PIN);

void drawController();
void drawControllerMessage(ControllerMessage message);

void setup() {
    Serial.begin(115200);

    joystick1.setup();
    joystick2.setup();
    // dPad.setup();
    buttonL.attach(BUTTON_L_PIN, INPUT_PULLUP);
    buttonR.attach(BUTTON_R_PIN, INPUT_PULLUP);
    display.setup();

    delay(250);
    display.clear();
    drawController();

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
        // controllerMessage.dPad = dPad.read();
        controllerMessage.buttonL = !buttonL.read();
        controllerMessage.buttonR = !buttonR.read();
        controllerMessage.touchPoint = display.read();

        if (!(prevControllerMessage == controllerMessage)) {
            // update display
            drawControllerMessage(controllerMessage);
            prevControllerMessage = controllerMessage;
        }
    }
}

void drawController() {
    // button L 
    display.fillRect(0.1 * DISPLAY_WIDTH, 0.05 * DISPLAY_HEIGHT, 0.2 * DISPLAY_WIDTH, 0.05 * DISPLAY_HEIGHT, HX8357_WHITE);
    // button R
    display.fillRect(0.7 * DISPLAY_WIDTH, 0.05 * DISPLAY_HEIGHT, 0.2 * DISPLAY_WIDTH, 0.05 * DISPLAY_HEIGHT, HX8357_WHITE);
    // joystick 1 
    display.fillRect(0.2 * DISPLAY_WIDTH - 0.2 * DISPLAY_HEIGHT, 0.15 * DISPLAY_HEIGHT, 
             0.4 * DISPLAY_HEIGHT, 0.4 * DISPLAY_HEIGHT, HX8357_WHITE);
    // joystick 2
    display.fillRect(0.8 * DISPLAY_WIDTH - 0.2 * DISPLAY_HEIGHT, 0.15 * DISPLAY_HEIGHT,
             0.4 * DISPLAY_HEIGHT, 0.4 * DISPLAY_HEIGHT, HX8357_WHITE);
    // rotary encoder
    display.fillCircle(0.5 * DISPLAY_WIDTH, 0.7 * DISPLAY_HEIGHT, 0.25 * DISPLAY_HEIGHT, HX8357_WHITE);
}

void drawControllerMessage(ControllerMessage message) {

    // button L
    if (!prevControllerMessage.buttonL && controllerMessage.buttonL)
        display.fillRect(0.1 * DISPLAY_WIDTH, 0.05 * DISPLAY_HEIGHT, 0.2 * DISPLAY_WIDTH, 0.05 * DISPLAY_HEIGHT, HX8357_RED);
    else if (prevControllerMessage.buttonL && !controllerMessage.buttonL) 
        display.fillRect(0.1 * DISPLAY_WIDTH, 0.05 * DISPLAY_HEIGHT, 0.2 * DISPLAY_WIDTH, 0.05 * DISPLAY_HEIGHT, HX8357_WHITE);
    
    // button R 
    if (!prevControllerMessage.buttonR && controllerMessage.buttonR)
        display.fillRect(0.7 * DISPLAY_WIDTH, 0.05 * DISPLAY_HEIGHT, 0.2 * DISPLAY_WIDTH, 0.05 * DISPLAY_HEIGHT, HX8357_RED);
    else if (prevControllerMessage.buttonR && !controllerMessage.buttonR)
        display.fillRect(0.7 * DISPLAY_WIDTH, 0.05 * DISPLAY_HEIGHT, 0.2 * DISPLAY_WIDTH, 0.05 * DISPLAY_HEIGHT, HX8357_WHITE);

    // joystick 1 
    if (!(prevControllerMessage.joystick1 == controllerMessage.joystick1)) {
        display.fillCircle(0.2 * DISPLAY_WIDTH + (prevControllerMessage.joystick1.x * 0.175)* DISPLAY_HEIGHT,
               (0.15 + 0.2 + prevControllerMessage.joystick1.y * 0.175) * DISPLAY_HEIGHT , 
               0.0245 * DISPLAY_HEIGHT, HX8357_WHITE);
        display.fillCircle(0.2 * DISPLAY_WIDTH + (controllerMessage.joystick1.x * 0.175)* DISPLAY_HEIGHT,
               (0.15 + 0.2 + controllerMessage.joystick1.y * 0.175) * DISPLAY_HEIGHT , 
               0.0245 * DISPLAY_HEIGHT, HX8357_BLUE);
    }
    
    // joystick 2
    if (!(prevControllerMessage.joystick2 == controllerMessage.joystick2)) {
        display.fillCircle(0.8 * DISPLAY_WIDTH + (prevControllerMessage.joystick2.x * 0.175)* DISPLAY_HEIGHT,
               (0.15 + 0.2 + prevControllerMessage.joystick2.y * 0.175) * DISPLAY_HEIGHT , 
               0.0245 * DISPLAY_HEIGHT, HX8357_WHITE);
        display.fillCircle(0.8 * DISPLAY_WIDTH + (controllerMessage.joystick2.x * 0.175)* DISPLAY_HEIGHT,
               (0.15 + 0.2 + controllerMessage.joystick2.y * 0.175) * DISPLAY_HEIGHT , 
               0.0245 * DISPLAY_HEIGHT, HX8357_BLUE);
    }
    
    // dpad
    // up
    if (!prevControllerMessage.dPad.up && controllerMessage.dPad.up)
        display.fillCircle(0.5 * DISPLAY_WIDTH, 0.5 * DISPLAY_HEIGHT, 0.05 * DISPLAY_HEIGHT, HX8357_RED);
    else if (prevControllerMessage.dPad.up && !controllerMessage.dPad.up) 
        display.fillCircle(0.5 * DISPLAY_WIDTH, 0.5 * DISPLAY_HEIGHT, 0.05 * DISPLAY_HEIGHT, HX8357_WHITE);
    //down
    if (!prevControllerMessage.dPad.down && controllerMessage.dPad.down)
        display.fillCircle(0.5 * DISPLAY_WIDTH, 0.9 * DISPLAY_HEIGHT, 0.05 * DISPLAY_HEIGHT, HX8357_RED);    
    else if (prevControllerMessage.dPad.down && !controllerMessage.dPad.down) 
        display.fillCircle(0.5 * DISPLAY_WIDTH, 0.9 * DISPLAY_HEIGHT, 0.05 * DISPLAY_HEIGHT, HX8357_WHITE);
    // left
    if (!prevControllerMessage.dPad.left && controllerMessage.dPad.left)
        display.fillCircle(0.5 * DISPLAY_WIDTH - 0.2 * DISPLAY_HEIGHT, 0.7 * DISPLAY_HEIGHT, 0.05 * DISPLAY_HEIGHT, HX8357_RED);    
    else if (prevControllerMessage.dPad.left && !controllerMessage.dPad.left) 
        display.fillCircle(0.5 * DISPLAY_WIDTH - 0.2 * DISPLAY_HEIGHT, 0.7 * DISPLAY_HEIGHT, 0.05 * DISPLAY_HEIGHT, HX8357_WHITE);
    // right
    if (!prevControllerMessage.dPad.right && controllerMessage.dPad.right)
        display.fillCircle(0.5 * DISPLAY_WIDTH + 0.2 * DISPLAY_HEIGHT, 0.7 * DISPLAY_HEIGHT, 0.05 * DISPLAY_HEIGHT, HX8357_RED);    
    else if (prevControllerMessage.dPad.right && !controllerMessage.dPad.right) 
        display.fillCircle(0.5 * DISPLAY_WIDTH + 0.2 * DISPLAY_HEIGHT, 0.7 * DISPLAY_HEIGHT, 0.05 * DISPLAY_HEIGHT, HX8357_WHITE);
    // select
    if (!prevControllerMessage.dPad.select && controllerMessage.dPad.select)
        display.fillCircle(0.5 * DISPLAY_WIDTH, 0.7 * DISPLAY_HEIGHT, 0.05 * DISPLAY_HEIGHT, HX8357_RED);    
    else if (prevControllerMessage.dPad.select && !controllerMessage.dPad.select) 
        display.fillCircle(0.5 * DISPLAY_WIDTH, 0.7 * DISPLAY_HEIGHT, 0.05 * DISPLAY_HEIGHT, HX8357_WHITE);
    // encoder
    display.fillCircle(0.5 * DISPLAY_WIDTH + 0.2 * cos(controllerMessage.dPad.encoderPosition) * DISPLAY_HEIGHT, 
               (0.7 + 0.2 * sin(controllerMessage.dPad.encoderPosition)) * DISPLAY_HEIGHT,
               0.0245 * DISPLAY_HEIGHT, HX8357_BLUE);
               
    // display touch
    // display.drawTouch(0.0125 * DISPLAY_HEIGHT, HX8357_GREEN);
}