#include <Arduino.h>

#include "app/app.h"

App app;

void setup() {
    app.setup();
}

void loop() {
    app.update();
}