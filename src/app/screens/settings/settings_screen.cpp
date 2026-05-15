#include "settings_screen.h"

#include <cstring>

#include "../../navigation/navigation.h"
#include "../../settings/settings_service.h"
#include "../../services/wifi/wifi_service.h"

void SettingsScreen::create()
{
    root = lv_obj_create(
        lv_scr_act());

    lv_obj_remove_style_all(root);

    lv_obj_set_style_bg_opa(
        root,
        LV_OPA_COVER,
        0);

    lv_obj_set_style_bg_color(
        root,
        lv_color_black(),
        0);

    lv_obj_set_size(
        root,
        LV_PCT(100),
        LV_PCT(100));

    Settings &settings =
        SettingsService::get();

    lv_obj_t *formContainer =
        lv_obj_create(root);

    lv_obj_remove_style_all(
        formContainer);

    lv_obj_set_size(
        formContainer,
        LV_PCT(100),
        170);

    lv_obj_align(
        formContainer,
        LV_ALIGN_TOP_LEFT,
        0,
        30);

    lv_obj_set_scroll_dir(
        formContainer,
        LV_DIR_VER);

    lv_obj_set_scrollbar_mode(
        formContainer,
        LV_SCROLLBAR_MODE_OFF);

    // ==========================
    // SETTINGS LABEL
    // ==========================

    lv_obj_t *label =
        lv_label_create(root);

    lv_label_set_text(
        label,
        "SETTINGS");

    lv_obj_set_style_text_color(
        label,
        lv_color_white(),
        0);

    lv_obj_set_style_text_font(
        label,
        &lv_font_montserrat_16,
        0);

    lv_obj_align(
        label,
        LV_ALIGN_TOP_LEFT,
        4,
        4);

    // ==========================
    // CONNECTION STATUS
    // ==========================

    wifiStatusLabel = lv_label_create(root);

    lv_obj_set_style_text_color(
        wifiStatusLabel,
        lv_palette_main(LV_PALETTE_GREEN),
        0);

    lv_obj_align(
        wifiStatusLabel,
        LV_ALIGN_TOP_RIGHT,
        -2,
        0);

    ipLabel = lv_label_create(root);

    lv_obj_set_style_text_color(
        ipLabel,
        lv_color_white(),
        0);

    lv_obj_align(
        ipLabel,
        LV_ALIGN_TOP_RIGHT,
        -2,
        18);

    // ==========================
    // WIFI SSID
    // ==========================

    lv_obj_t *ssidLabel =
        lv_label_create(formContainer);

    lv_label_set_text(
        ssidLabel,
        "WiFi SSID");

    lv_obj_set_style_text_color(
        ssidLabel,
        lv_color_white(),
        0);

    lv_obj_align(
        ssidLabel,
        LV_ALIGN_TOP_LEFT,
        10,
        35);

    ssidInput =
        lv_textarea_create(formContainer);

    lv_textarea_set_text(
        ssidInput,
        settings.wifiSsid);

    lv_obj_set_size(
        ssidInput,
        150,
        32);

    lv_obj_align(
        ssidInput,
        LV_ALIGN_TOP_LEFT,
        5,
        55);

    lv_obj_add_event_cb(
        ssidInput,
        onTextareaFocused,
        LV_EVENT_FOCUSED,
        this);

    // ==========================
    // WIFI PASSWORD
    // ==========================

    lv_obj_t *passwordLabel =
        lv_label_create(formContainer);

    lv_label_set_text(
        passwordLabel,
        "WiFi Password");

    lv_obj_set_style_text_color(
        passwordLabel,
        lv_color_white(),
        0);

    lv_obj_align(
        passwordLabel,
        LV_ALIGN_TOP_LEFT,
        170,
        35);

    passwordInput =
        lv_textarea_create(formContainer);

    lv_textarea_set_text(
        passwordInput,
        settings.wifiPassword);

    lv_textarea_set_password_mode(
        passwordInput,
        true);

    lv_obj_set_size(
        passwordInput,
        150,
        32);

    lv_obj_align(
        passwordInput,
        LV_ALIGN_TOP_LEFT,
        165,
        55);

    lv_obj_add_event_cb(
        passwordInput,
        onTextareaFocused,
        LV_EVENT_FOCUSED,
        this);

    // ==========================
    // EDOL AMS Host
    // ==========================

    lv_obj_t *amsHostLabel =
        lv_label_create(formContainer);

    lv_label_set_text(
        amsHostLabel,
        "EDOL AMS Host");

    lv_obj_set_style_text_color(
        amsHostLabel,
        lv_color_white(),
        0);

    lv_obj_align(
        amsHostLabel,
        LV_ALIGN_TOP_LEFT,
        10,
        91);

    amsHostInput =
        lv_textarea_create(formContainer);

    lv_textarea_set_text(
        amsHostInput,
        settings.amsHost);

    lv_obj_set_size(
        amsHostInput,
        205,
        32);

    lv_obj_align(
        amsHostInput,
        LV_ALIGN_TOP_LEFT,
        5,
        111);

    lv_obj_add_event_cb(
        amsHostInput,
        onTextareaFocused,
        LV_EVENT_FOCUSED,
        this);

    // ==========================
    // EDOL AMS Port
    // ==========================

    lv_obj_t *amsPortLabel =
        lv_label_create(formContainer);

    lv_label_set_text(
        amsPortLabel,
        "Port");

    lv_obj_set_style_text_color(
        amsPortLabel,
        lv_color_white(),
        0);

    lv_obj_align(
        amsPortLabel,
        LV_ALIGN_TOP_LEFT,
        225,
        91);

    amsPortInput =
        lv_textarea_create(formContainer);

    char amsPortText[16];

    sprintf(
        amsPortText,
        "%d",
        settings.amsPort);

    lv_textarea_set_text(
        amsPortInput,
        amsPortText);

    lv_obj_set_size(
        amsPortInput,
        95,
        32);

    lv_obj_align(
        amsPortInput,
        LV_ALIGN_TOP_LEFT,
        220,
        111);

    lv_obj_add_event_cb(
        amsPortInput,
        onTextareaFocused,
        LV_EVENT_FOCUSED,
        this);

    // ==========================
    // SPACER
    // ==========================

    lv_obj_t *spacer =
        lv_obj_create(formContainer);

    lv_obj_remove_style_all(
        spacer);

    lv_obj_set_size(
        spacer,
        1,
        120);

    lv_obj_align(
        spacer,
        LV_ALIGN_TOP_LEFT,
        0,
        270);

    // ==========================
    // BACK BUTTON
    // ==========================
    backButton =
        lv_btn_create(root);

    lv_obj_set_size(
        backButton,
        80,
        32);

    lv_obj_align(
        backButton,
        LV_ALIGN_BOTTOM_LEFT,
        10,
        -10);

    lv_obj_t *buttonLabel =
        lv_label_create(
            backButton);

    lv_label_set_text(
        buttonLabel,
        "< BACK");

    lv_obj_center(buttonLabel);

    lv_obj_add_event_cb(
        backButton,
        onBackClick,
        LV_EVENT_CLICKED,
        NULL);

    // ==========================
    // SAVE BUTTON
    // ==========================
    saveButton =
        lv_btn_create(root);

    lv_obj_set_size(
        saveButton,
        80,
        32);

    lv_obj_align(
        saveButton,
        LV_ALIGN_BOTTOM_RIGHT,
        -10,
        -10);

    lv_obj_t *saveButtonLabel =
        lv_label_create(
            saveButton);

    lv_label_set_text(
        saveButtonLabel,
        "SAVE");

    lv_obj_center(saveButtonLabel);

    lv_obj_add_event_cb(
        saveButton,
        onSaveClick,
        LV_EVENT_CLICKED,
        this);

    // ==========================
    // KEYBOARD
    // ==========================

    keyboard =
        lv_keyboard_create(root);

    lv_obj_set_size(
        keyboard,
        LV_PCT(100),
        120);

    lv_obj_align(
        keyboard,
        LV_ALIGN_BOTTOM_MID,
        0,
        0);

    lv_obj_add_flag(
        keyboard,
        LV_OBJ_FLAG_HIDDEN);

    lv_obj_add_event_cb(
        keyboard,
        onKeyboardEvent,
        LV_EVENT_ALL,
        this);

    statusTimer =
        lv_timer_create(
            updateConnectionStatus,
            1000,
            this);

    updateConnectionStatus(
        statusTimer);
}

void SettingsScreen::destroy()
{
    if (root)
    {
        if (statusTimer)
        {
            lv_timer_del(statusTimer);

            statusTimer = nullptr;
        }
        lv_obj_del(root);
        root = nullptr;
    }
}

void SettingsScreen::onBackClick(
    lv_event_t *event)
{
    Navigation::back();
}

void SettingsScreen::onTextareaFocused(
    lv_event_t *event)
{
    SettingsScreen *screen =
        static_cast<SettingsScreen *>(
            lv_event_get_user_data(event));

    lv_obj_t *textarea =
        lv_event_get_target(event);

    lv_keyboard_set_textarea(
        screen->keyboard,
        textarea);

    lv_obj_clear_flag(
        screen->keyboard,
        LV_OBJ_FLAG_HIDDEN);

    lv_coord_t y =
        lv_obj_get_y(textarea);

    lv_obj_scroll_to_y(
        lv_obj_get_parent(textarea),
        y - 20,
        LV_ANIM_OFF);
}

void SettingsScreen::onKeyboardEvent(
    lv_event_t *event)
{
    SettingsScreen *screen =
        static_cast<SettingsScreen *>(
            lv_event_get_user_data(event));

    lv_event_code_t code =
        lv_event_get_code(event);

    if (code != LV_EVENT_READY)
    {
        return;
    }

    if (!screen->keyboard)
    {
        return;
    }

    lv_obj_add_flag(
        screen->keyboard,
        LV_OBJ_FLAG_HIDDEN);

    lv_keyboard_set_textarea(
        screen->keyboard,
        NULL);
}

void SettingsScreen::onSaveClick(
    lv_event_t *event)
{
    SettingsScreen *screen =
        static_cast<SettingsScreen *>(
            lv_event_get_user_data(event));

    Settings &settings =
        SettingsService::get();

    strncpy(
        settings.wifiSsid,
        lv_textarea_get_text(
            screen->ssidInput),
        sizeof(settings.wifiSsid) - 1);

    settings.wifiSsid[sizeof(settings.wifiSsid) - 1] = '\0';

    strncpy(
        settings.wifiPassword,
        lv_textarea_get_text(
            screen->passwordInput),
        sizeof(settings.wifiPassword) - 1);

    settings.wifiPassword[sizeof(settings.wifiPassword) - 1] = '\0';

    strncpy(
        settings.amsHost,
        lv_textarea_get_text(
            screen->amsHostInput),
        sizeof(settings.amsHost) - 1);

    settings.amsHost[sizeof(settings.amsHost) - 1] = '\0';

    settings.amsPort =
        atoi(
            lv_textarea_get_text(
                screen->amsPortInput));

    SettingsService::save();

    // ==========================
    // TOAST
    // ==========================

    lv_obj_t *toast =
        lv_obj_create(
            screen->root);

    lv_obj_set_size(
        toast,
        140,
        36);

    lv_obj_align(
        toast,
        LV_ALIGN_BOTTOM_MID,
        0,
        -50);

    lv_obj_set_style_bg_color(
        toast,
        lv_palette_main(
            LV_PALETTE_GREEN),
        0);

    lv_obj_set_style_border_width(
        toast,
        2,
        0);

    lv_obj_set_style_border_color(
        toast,
        lv_color_black(),
        0);

    lv_obj_set_style_radius(
        toast,
        6,
        0);

    lv_obj_t *toastLabel =
        lv_label_create(toast);

    lv_label_set_text(
        toastLabel,
        "Settings Saved");

    lv_obj_set_style_text_color(
        toastLabel,
        lv_color_black(),
        0);

    lv_obj_center(toastLabel);

    lv_timer_t *timer =
        lv_timer_create(
            hideToast,
            1500,
            toast);

    lv_timer_set_repeat_count(
        timer,
        1);
}

void SettingsScreen::hideToast(
    lv_timer_t *timer)
{
    lv_obj_t *toast =
        static_cast<lv_obj_t *>(
            timer->user_data);

    lv_obj_del(toast);
}

void SettingsScreen::updateConnectionStatus(
    lv_timer_t *timer)
{
    SettingsScreen *screen =
        static_cast<SettingsScreen *>(
            timer->user_data);

    if (WifiService::isConnected())
    {

        lv_label_set_text(
            screen->wifiStatusLabel,
            "WiFi: Connected");

        lv_obj_set_style_text_color(
            screen->wifiStatusLabel,
            lv_palette_main(
                LV_PALETTE_GREEN),
            0);

        lv_label_set_text(
            screen->ipLabel,
            WifiService::getIp()
                .c_str());
    }
    else
    {

        lv_label_set_text(
            screen->wifiStatusLabel,
            "WiFi: Disconnected");

        lv_obj_set_style_text_color(
            screen->wifiStatusLabel,
            lv_palette_main(
                LV_PALETTE_RED),
            0);

        lv_label_set_text(
            screen->ipLabel,
            "-");
    }
}