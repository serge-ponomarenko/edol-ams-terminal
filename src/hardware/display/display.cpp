#include "display.h"

#include <Arduino.h>
#include <TFT_eSPI.h>
#include <stdint.h>

#include "config/pins.h"

TFT_eSPI tft;

static unsigned long lastActivity = 0;

static bool dimmed = false;

void displaySetup()
{
    pinMode(TFT_BL, OUTPUT);

    ledcSetup(0, 5000, 8);

    ledcAttachPin(TFT_BL, 0);

    displaySetBrightness(100);

    lastActivity = millis();

    tft.init();

    tft.setRotation(1); // Horizontal. USB on the right
    // tft.setRotation(3);     // Horizontal. USB on the left

    tft.invertDisplay(false);
}

void displaySetBrightness(
    uint8_t percent)
{
    percent =
        constrain(
            percent,
            0,
            100);

    uint8_t value =
        map(
            percent,
            0,
            100,
            0,
            255);

    ledcWrite(0, value);
}

static bool wakeConsumed = false;

void displayTouch()
{
    lastActivity = millis();

    if (dimmed)
    {
        displaySetBrightness(100);
        dimmed = false;
        wakeConsumed = true;
    }
}

void displayUpdate()
{
    if (
        !dimmed &&
        millis() - lastActivity > 60000)
    {
        displaySetBrightness(5);

        dimmed = true;
    }
}

bool displayConsumeWake()
{
    if (!wakeConsumed)
    {
        return false;
    }
    wakeConsumed = false;
    return true;
}