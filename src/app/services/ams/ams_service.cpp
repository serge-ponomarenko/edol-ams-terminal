#include "ams_service.h"

#include "../../../utils/json/json_utils.h"

#include "../../settings/settings_service.h"
#include "../wifi/wifi_service.h"
#include "../http/http_service.h"

AmsState AmsService::state;

unsigned long AmsService::lastFetch = 0;
int AmsService::requestId = -1;

void AmsService::begin()
{
}

void AmsService::update()
{
    if (!WifiService::isConnected())
    {
        return;
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
            Serial.print(F("AMS request failed: "));
            Serial.println(HttpService::getResponseCode(requestId));
            HttpService::clear(requestId);
            requestId = -1;
            return;
        }

        String body = HttpService::getResponse(requestId);
        HttpService::clear(requestId);
        requestId = -1;

        state.activeSlot = extractJsonInt(body, "activeSlot");
        state.humidity = extractJsonInt(body, "humidityRaw");
        state.temperature = extractJsonFloat(body, "temperature");

        String extTray = extractJsonObject(body, "extTray");
        state.slots[4].slot = "EXT";
        state.slots[4].id = extractJsonInt(extTray, "spoolId");
        state.slots[4].isActive = extractJsonBool(extTray, "active");
        state.slots[4].isEmpty = extractJsonBool(extTray, "empty");
        state.slots[4].weight = extractJsonInt(extTray, "remaining");
        state.slots[4].material = extractJsonString(extTray, "material");
        state.slots[4].vendor = extractJsonString(extTray, "vendor");
        state.slots[4].brand = extractJsonString(extTray, "brand");
        state.slots[4].color = extractJsonString(extTray, "color");

        for (int i = 0; i < 4; i++)
        {
            String slot = extractJsonArrayObject(body, "slots", i);
            char slotName[3];
            snprintf(slotName, sizeof(slotName), "A%d", i + 1);
            state.slots[i].slot = slotName;
            state.slots[i].id = extractJsonInt(slot, "spoolId");
            state.slots[i].isActive = extractJsonBool(slot, "active");
            state.slots[i].isEmpty = extractJsonBool(slot, "empty");
            state.slots[i].weight = extractJsonInt(slot, "remaining");
            state.slots[i].material = extractJsonString(slot, "material");
            state.slots[i].vendor = extractJsonString(slot, "vendor");
            state.slots[i].brand = extractJsonString(slot, "brand");
            state.slots[i].color = extractJsonString(slot, "color");
        }

        state.loaded = true;

        Serial.println(F("AMS state updated"));

        return;
    }

    // ==========================
    // START REQUEST
    // ==========================

    unsigned long now = millis();

    if (now - lastFetch < 3000)
    {
        return;
    }

    lastFetch = now;

    Settings &settings = SettingsService::get();
    char url[128];
    snprintf(
        url,
        sizeof(url),
        "http://%s:%d/ams/state",
        settings.amsHost,
        settings.amsPort);

    Serial.println(F("Fetching AMS state..."));
    requestId = HttpService::get(url);
}

AmsState &AmsService::getState()
{
    return state;
}