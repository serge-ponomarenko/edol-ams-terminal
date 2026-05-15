#pragma once

#include <Arduino.h>

constexpr uint8_t EDOL_NFC_PAGE = 8;

struct __attribute__((packed)) EdolNfcData
{
    char magic[4];

    uint8_t version;

    uint8_t type;

    uint16_t reserved;

    uint32_t spoolId;

    uint32_t crc;
};

enum class NfcReadResult
{
    OK,
    NO_TAG,
    INVALID_TAG,
    INVALID_VERSION,
    INVALID_CRC
};

void nfcSetup();

bool nfcIsTagPresent();

bool nfcReadTag(
    uint8_t *uid,
    uint8_t *uidLength
);

bool nfcWriteEdolTag(
    uint32_t spoolId
);

NfcReadResult nfcReadEdolTag(
    EdolNfcData &data
);