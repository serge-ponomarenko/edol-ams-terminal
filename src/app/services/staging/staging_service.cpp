#include "staging_service.h"

#include "../../../utils/json/json_utils.h"

#include "../nfc/nfc_service.h"
#include "../../settings/settings_service.h"
#include "../wifi/wifi_service.h"
#include "../http/http_service.h"
#include "../ams/ams_service.h"

Spool StagingService::spool;

bool StagingService::hasSpool()
{
    return loaded;
}

Spool &StagingService::getSpool()
{
    return spool;
}

void StagingService::update()
{
    if (!WifiService::isConnected())
    {
        return;
    }

    if (assignRequestId >= 0)
    {
        if (HttpService::isCompleted(assignRequestId))
        {
            HttpService::clear(assignRequestId);
            assignRequestId = -1;
        }
    }

    if (loaded && millis() - lastScanTime > 30000)
    {
        clear();
    }

    // ==========================
    // WAITING RESPONSE
    // ==========================

    if (requestId >= 0)
    {
        if (!HttpService::isCompleted(requestId))
        {
            return;
        }

        if (!HttpService::isSuccess(requestId))
        {
            Serial.println(F("STAGING RESOLVE FAILED"));
            HttpService::clear(requestId);
            requestId = -1;
            return;
        }

        String body = HttpService::getResponse(requestId);

        HttpService::clear(requestId);

        requestId = -1;

        loaded = true;

        lastScanTime = millis();

        version++;

        spool.id = extractJsonInt(body, "spoolId");
        spool.weight = extractJsonInt(body, "remaining");
        spool.vendor = extractJsonString(body, "vendor");
        spool.brand = extractJsonString(body, "brand");
        spool.material = extractJsonString(body, "material");
        spool.color = extractJsonString(body, "color");

        if (spool.color.isEmpty())
        {
            spool.color = "#303030";
        }

        Serial.println(F("=== STAGING SPOOL ==="));

        Serial.print(F("ID: "));
        Serial.println(spool.id);

        return;
    }

    // ==========================
    // NEW NFC SCAN
    // ==========================

    if (!NfcService::hasPendingScan())
    {
        return;
    }

    uint32_t spoolId = NfcService::consumePendingScan();

    Settings &settings = SettingsService::get();

    String url =
        String("http://") +
        settings.amsHost +
        ":" +
        settings.amsPort +
        "/ams/find?id=" +
        spoolId;

    Serial.print(F("Resolving spool: "));
    Serial.println(spoolId);

    requestId = HttpService::get(url);
}

void StagingService::clear()
{
    loaded = false;
    spool = Spool();
    version++;
}

void StagingService::assignToSlot(
    uint8_t slot)
{
    if (!loaded)
    {
        return;
    }

    Settings &settings = SettingsService::get();

    String url =
        String("http://") +
        settings.amsHost +
        ":" +
        settings.amsPort +
        "/ams/set-spool?id=" +
        spool.id +
        "&slot=" +
        slot;

    assignRequestId = HttpService::get(url);

    Serial.print(F("Assign spool "));
    Serial.print(spool.id);
    Serial.print(F(" to slot "));
    Serial.println(slot);

    clear();
}

uint32_t StagingService::getVersion()
{
    return version;
}

void StagingService::keepAlive()
{
    if (!loaded)
    {
        return;
    }
    lastScanTime = millis();
}