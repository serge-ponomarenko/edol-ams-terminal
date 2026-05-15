#pragma once

#include "ams_state.h"

class AmsService {

public:

    static void begin();

    static void update();

    static AmsState& getState();

private:

    static AmsState state;

    static unsigned long lastFetch;

    static int requestId;
};