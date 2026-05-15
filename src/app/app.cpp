#include "app.h"

#include <memory>

#include "../hardware/display/display.h"
#include "../hardware/touch/touch.h"
#include "../hardware/nfc/nfc.h"

#include "../ui/ui.h"

#include "navigation/navigation.h"
#include "screens/home/home_screen.h"
#include "screens/loading/loading_screen.h"
#include "settings/settings_service.h"
#include "services/wifi/wifi_service.h"
#include "services/ams/ams_service.h"
#include "services/nfc/nfc_service.h"
#include "services/staging/staging_service.h"
#include "services/http/http_service.h"
#include "screens/settings/settings_screen.h"

LoadingScreen *App::loadingScreen = nullptr;

void App::setup()
{
    Serial.begin(115200);
    delay(1000);
    Serial.println(F("EDOL AMS Boot"));

    displaySetup();

    touchSetup();

    uiSetup();

    SettingsService::begin();

    WifiService::begin();

    AmsService::begin();

    nfcSetup();

    if (SettingsService::get().wifiSsid[0] == '\0')
    {
        Navigation::push(new SettingsScreen());
    }
    else
    {
        LoadingScreen *screen = new LoadingScreen();
        loadingScreen = screen;
        Navigation::push(screen);
    }
}

EdolNfcData data;

void App::update()
{
    touchLoop();

    if (displayConsumeWake())
    {
        delay(500);
        return;
    }

    displayUpdate();

    WifiService::update();

    HttpService::update();

    AmsService::update();

    NfcService::update();

    StagingService::update();

    if (
        !appReady &&
        loadingScreen &&
        loadingScreen->root)
    {
        if (!WifiService::isConnected())
        {
            loadingScreen->setStatus("Connecting WiFi...");
        }
        else if (!AmsService::getState().loaded)
        {
            loadingScreen->setStatus("Loading AMS...");
        }
        else
        {
            appReady = true;
            Navigation::replace(new HomeScreen());
        }
    }

    uiLoop();
}