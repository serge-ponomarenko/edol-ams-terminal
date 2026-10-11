#pragma once

#include <Arduino.h>

class TerminalCredentialStore {
public:
    static bool hasCredential();
    static bool save(const String &terminalId, const String &secret);
    static bool load(String &terminalId, String &secret);
    static void clear();
};
