#pragma once

#include <stdint.h>

void displaySetup();

void displaySetBrightness(uint8_t percent);

void displayTouch();

void displayUpdate();

bool displayConsumeWake();