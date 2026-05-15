#pragma once

#include <Arduino.h>

class WifiService {

public:

    static void begin();

    static void update();

    static bool isConnected();

    static String getIp();

private:

    static unsigned long lastReconnectAttempt;
};