#pragma once

#include "../../../models/spool/spool.h"

struct AmsState {

    bool loaded = false;

    int activeSlot = -1;

    int humidity = 0;

    float temperature = 0;

    int currentLayer = 0;
    int totalLayers = 0;

    Spool slots[5];
};