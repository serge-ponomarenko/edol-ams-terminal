#pragma once

#include <lvgl.h>

#include "../screen.h"
#include "../../settings/settings.h"

class SettingsScreen : public Screen
{
public:
    void create() override;
    void destroy() override;

private:
    lv_obj_t *root = nullptr;
    lv_obj_t *backButton = nullptr;
    lv_obj_t *saveButton = nullptr;
    lv_obj_t *keyboard = nullptr;

    lv_obj_t *wifiStatusLabel = nullptr;
    lv_obj_t *ipLabel = nullptr;

    lv_obj_t *ssidInput = nullptr;
    lv_obj_t *passwordInput = nullptr;
    lv_obj_t *amsHostInput = nullptr;
    lv_obj_t *amsPortInput = nullptr;

    lv_timer_t *statusTimer = nullptr;

    static void onBackClick(
        lv_event_t *event);

    static void onSaveClick(
        lv_event_t *event);

    static void onTextareaFocused(
        lv_event_t *event);

    static void onKeyboardEvent(
        lv_event_t *event);

    static void hideToast(
        lv_timer_t *timer);

    static void updateConnectionStatus(
        lv_timer_t *timer);
};
