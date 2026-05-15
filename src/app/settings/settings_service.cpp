#include "settings_service.h"

#include <LittleFS.h>
#include <cstring>

#include "../../utils/json/json_utils.h"

Settings SettingsService::settings;

static const char *SETTINGS_FILE =
    "/settings.json";

void SettingsService::begin()
{
    if (!LittleFS.begin(true))
    {
        Serial.println(F(
            "LittleFS mount failed"));
        return;
    }

    if (!load())
    {
        strcpy(settings.wifiSsid, "");
        strcpy(settings.wifiPassword, "");
        strcpy(settings.amsHost, "192.168.0.200");
        settings.amsPort = 8099;
        save();
    }
}

Settings &SettingsService::get()
{
    return settings;
}

bool SettingsService::save()
{
    File file = LittleFS.open(SETTINGS_FILE, "w");

    if (!file)
    {
        Serial.println(
            F("Failed to open settings file for writing"));

        return false;
    }

    char json[512];

    snprintf(
        json,
        sizeof(json),
        "{"
        "\"wifiSsid\":\"%s\","
        "\"wifiPassword\":\"%s\","
        "\"amsHost\":\"%s\","
        "\"amsPort\":%d"
        "}",
        settings.wifiSsid,
        settings.wifiPassword,
        settings.amsHost,
        settings.amsPort
    );

    file.print(json);

    file.close();

    ESP.restart();

    return true;
}

bool SettingsService::load()
{
    if (!LittleFS.exists(SETTINGS_FILE))
    {
        // Serial.println(F("Settings file does not exist"));
        return false;
    }

    File file = LittleFS.open(SETTINGS_FILE, "r");
    if (!file)
    {
        // Serial.println(F("Failed to open settings file"));
        return false;
    }

    String json = file.readString();

    file.close();
    strcpy(settings.wifiSsid, extractJsonString(json, "wifiSsid").c_str());
    strcpy(settings.wifiPassword, extractJsonString(json, "wifiPassword").c_str());
    strcpy(settings.amsHost, extractJsonString(json, "amsHost").c_str());
    settings.amsPort = extractJsonInt(json, "amsPort");

    Serial.println(F("Settings loaded"));

    return true;
}