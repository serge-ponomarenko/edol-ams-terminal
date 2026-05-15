#include "nfc.h"

#include <Wire.h>
#include <Adafruit_PN532.h>

#include "config/pins.h"

Adafruit_PN532 nfc(
    PN532_SDA,
    PN532_SCL);

static uint32_t calculateCrc(
    const EdolNfcData &data)
{
    uint32_t crc = 0;

    for (int i = 0; i < 4; i++)
    {
        crc =
            (crc * 31) +
            data.magic[i];
    }

    crc =
        (crc * 31) +
        data.version;

    crc =
        (crc * 31) +
        data.type;

    crc =
        (crc * 31) +
        ((data.spoolId >> 24) & 0xFF);

    crc =
        (crc * 31) +
        ((data.spoolId >> 16) & 0xFF);

    crc =
        (crc * 31) +
        ((data.spoolId >> 8) & 0xFF);

    crc =
        (crc * 31) +
        (data.spoolId & 0xFF);

    return crc;
}

void nfcSetup()
{
    Wire.begin(
        PN532_SDA,
        PN532_SCL);

    nfc.begin();

    uint32_t version = nfc.getFirmwareVersion();

    if (!version)
    {
        Serial.println(F("PN532 NOT FOUND"));
        while (1)
        {
            delay(10);
        }
    }

    nfc.SAMConfig();
    Serial.println(F("PN532 Ready"));
}

bool nfcReadTag(
    uint8_t *uid,
    uint8_t *uidLength)
{
    return nfc.readPassiveTargetID(
        PN532_MIFARE_ISO14443A,
        uid,
        uidLength,
        50);
}

bool nfcWriteEdolTag(
    uint32_t spoolId)
{
    uint8_t uid[7];

    uint8_t uidLength;

    bool tagPresent =
        nfcReadTag(
            uid,
            &uidLength);

    if (!tagPresent)
    {
        return false;
    }

    delay(50);

    EdolNfcData data;

    memset(&data, 0, sizeof(data));

    memcpy(
        data.magic,
        "EDOL",
        4);

    data.version = 1;

    data.type = 1;

    data.reserved = 0;

    data.spoolId = spoolId;

    data.crc =
        calculateCrc(data);

    uint8_t *raw =
        (uint8_t *)&data;

    for (int i = 0; i < 4; i++)
    {
        bool success =
            nfc.ntag2xx_WritePage(
                EDOL_NFC_PAGE + i,
                raw + (i * 4));

        if (!success)
        {
            Serial.println(F("NFC WRITE FAILED"));
            return false;
        }
    }

    Serial.println(F("NFC WRITE SUCCESS"));
    return true;
}

NfcReadResult nfcReadEdolTag(
    EdolNfcData &data)
{
    uint8_t uid[7];

    uint8_t uidLength;

    bool tagPresent = nfcReadTag(uid, &uidLength);

    if (!tagPresent)
    {
        return NfcReadResult::NO_TAG;
    }

    uint8_t raw[16];

    for (int i = 0; i < 4; i++)
    {
        bool success =
            nfc.ntag2xx_ReadPage(
                EDOL_NFC_PAGE + i,
                raw + (i * 4));

        if (!success)
        {
            return NfcReadResult::INVALID_TAG;
        }
    }

    memcpy(&data, raw, sizeof(EdolNfcData));

    if (memcmp( data.magic, "EDOL", 4) != 0)
    {
        return NfcReadResult::INVALID_TAG;
    }

    if (data.version != 1)
    {
        return NfcReadResult::INVALID_VERSION;
    }

    uint32_t expectedCrc = calculateCrc(data);

    if (data.crc != expectedCrc)
    {
        return NfcReadResult::INVALID_CRC;
    }

    return NfcReadResult::OK;
}

bool nfcIsTagPresent()
{
    uint8_t uid[7];
    uint8_t uidLength;
    return nfcReadTag(uid, &uidLength);
}