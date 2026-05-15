#pragma once

#include <stdint.h>

enum class NfcWriteState
{
    IDLE,
    WAITING_FOR_TAG,
    SUCCESS,
    ERROR
};

class NfcService
{

public:
    static void update();

    static void startWrite(
        uint32_t spoolId);

    static void cancel();

    static bool isBusy();

    static NfcWriteState getState();

    static bool hasPendingScan();

    static uint32_t consumePendingScan();

private:
    static inline NfcWriteState state = NfcWriteState::IDLE;

    static inline uint32_t pendingSpoolId = 0;

    static inline unsigned long stateChangedAt = 0;

    static inline uint32_t pendingScanSpoolId = 0;

    static inline bool pendingScan = false;

    static inline bool tagPresent = false;

    static inline uint8_t missingPolls = 0;

};