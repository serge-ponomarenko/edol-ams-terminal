#include "touch.h"

#include <SPI.h>
#include <XPT2046_Touchscreen.h>

#include "config/pins.h"

#include "../display/display.h"

SPIClass touchSPI(HSPI);

XPT2046_Touchscreen ts(
    TOUCH_CS,
    TOUCH_IRQ
);

static bool pressed = false;
static int x = 0;
static int y = 0;

int mapTouchX(int rawX) {
    return constrain(
        map(rawX, 180, 3820, 0, 320),
        0,
        319
    );
}

int mapTouchY(int rawY) {
    return constrain(
        map(rawY, 230, 3880, 0, 240),
        0,
        239
    );
}

void touchSetup() {
    touchSPI.begin(
        TOUCH_SCK,
        TOUCH_MISO,
        TOUCH_MOSI,
        TOUCH_CS
    );

    ts.begin(touchSPI);

    ts.setRotation(1);   // Horizontal. USB on the right
    //ts.setRotation(3);     // Horizontal. USB on the left
}

void touchLoop() {
    if (ts.touched()) {

        TS_Point p = ts.getPoint();

        pressed = true;

        displayTouch();

        x = mapTouchX(p.x);
        y = mapTouchY(p.y);

    } else {

        pressed = false;
    }
}

bool touchIsPressed() {
    return pressed;
}

int touchGetX() {
    return x;
}

int touchGetY() {
    return y;
}