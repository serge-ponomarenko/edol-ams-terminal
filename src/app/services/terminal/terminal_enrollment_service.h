#pragma once

#include <Arduino.h>

class TerminalEnrollmentService {
public:
    static void update();
    static bool start(const String &pairingCode);
    static bool isBusy();
    static const String &lastError();

private:
    static inline int requestId = -1;
    static inline String error;
};
