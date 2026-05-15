#include "wifi_service.h"

#include <WiFi.h>

#include "../../settings/settings_service.h"

unsigned long
    WifiService::lastReconnectAttempt = 0;

void WifiService::begin()
{
    WiFi.mode(WIFI_STA);

    WiFi.setAutoReconnect(true);

    WiFi.persistent(false);

    Settings &settings =
        SettingsService::get();

    if (settings.wifiSsid[0] == '\0')
    {
        return;
    }

    Serial.println(F("Connecting to WiFi..."));

    WiFi.begin(settings.wifiSsid, settings.wifiPassword);
}

void WifiService::update()
{
    if (WiFi.status() == WL_CONNECTED)
    {
        return;
    }

    unsigned long now = millis();

    if (now - lastReconnectAttempt < 10000)
    {
        return;
    }

    lastReconnectAttempt = now;

    Settings &settings = SettingsService::get();

    if (settings.wifiSsid[0] == '\0')
    {
        return;
    }

    Serial.println(F("Reconnecting WiFi..."));

    WiFi.disconnect();

    WiFi.begin(
        settings.wifiSsid,
        settings.wifiPassword);
}

bool WifiService::isConnected()
{
    return WiFi.status() == WL_CONNECTED;
}

String WifiService::getIp()
{
    if (!isConnected())
    {
        return "-";
    }

    return WiFi.localIP()
        .toString();
}