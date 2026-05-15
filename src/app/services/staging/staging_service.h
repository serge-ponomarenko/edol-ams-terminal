#pragma once

#include "../../../models/spool/spool.h"

class StagingService
{

public:
    static void update();

    static bool hasSpool();

    static Spool &getSpool();

    static uint32_t getVersion();

    static void assignToSlot(uint8_t slot);

    static void keepAlive();

    static void clear();

private:

    static inline bool loaded = false;

    static Spool spool;

    static inline int requestId = -1;

    static inline int assignRequestId = -1;

    static inline uint32_t version = 0;

    static inline unsigned long lastScanTime = 0;
};