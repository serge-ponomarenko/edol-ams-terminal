#pragma once

#include <Arduino.h>

class TerminalApi {
public:
    static bool isReady();
    static String authorization();
    static String url(const char *path);
    static void factoryReset();
};
