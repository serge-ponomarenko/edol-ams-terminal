#pragma once
#include <lvgl.h>

#include "../screen.h"

#include "../../../models/spool/spool.h"
#include "../../../ui/widgets/slot_card_v2/slot_card_v2.h"

class HomeScreen : public Screen
{
public:
    void create() override;
    void destroy() override;

    static void refreshNow();

private:
    static HomeScreen *activeScreen;

    lv_obj_t *contentContainer = nullptr;
    lv_obj_t *overlayContainer = nullptr;
    lv_obj_t *root = nullptr;
    lv_obj_t *settingsButton;

    lv_obj_t *stagingContainer = nullptr;
    lv_obj_t *stagingHeaderLabel = nullptr; // Scanned. Tap for actions
    lv_obj_t *stagingTitleLabel = nullptr;
    lv_obj_t *stagingIdLabel = nullptr;
    lv_obj_t *stagingWeightLabel = nullptr;

    lv_obj_t *infoWifiLabel = nullptr;
    lv_obj_t *infoAmsLabel = nullptr;
    lv_obj_t *infoTempLabel = nullptr;
    lv_obj_t *infoHumidityLabel = nullptr;

    char stagingTitle[64];
    char stagingWeight[16];
    char stagingId[10];

    SlotCardV2 cards[5];

    lv_timer_t *refreshTimer = nullptr;
    lv_obj_t *slotModal = nullptr;
    lv_obj_t *toast = nullptr;
    lv_timer_t *toastTimer = nullptr;
    char toastText[64];

    static void onSettingsClick(lv_event_t *event);
    static void onStagingClick(lv_event_t *event);
    static void onSlotClick(lv_event_t *event);
    static void onCancelSlotClick(lv_event_t *event);
    static void hideToast(lv_timer_t *timer);

    static void refreshCards(lv_timer_t *timer);
};
