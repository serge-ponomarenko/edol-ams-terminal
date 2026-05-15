#include "home_screen.h"

#include "../../navigation/navigation.h"
#include "../settings/settings_screen.h"

#include "../../../../src/utils/utils.h"

#include "../../../ui/widgets/slot_card_v2/slot_card_v2.h"

#include "../../services/ams/ams_service.h"
#include "../../services/staging/staging_service.h"

#include <memory>

HomeScreen *HomeScreen::activeScreen = nullptr;

void HomeScreen::create()
{
    root = lv_obj_create(
        lv_scr_act());

    lv_obj_remove_style_all(root);

    lv_obj_set_size(
        root,
        LV_PCT(100),
        LV_PCT(100));

    contentContainer =
        lv_obj_create(root);

    lv_obj_remove_style_all(
        contentContainer);

    lv_obj_clear_flag(
        contentContainer,
        LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_size(
        contentContainer,
        LV_PCT(100),
        LV_PCT(100));

    lv_obj_set_style_bg_opa(
        contentContainer,
        LV_OPA_COVER,
        0);

    lv_obj_set_style_bg_color(
        contentContainer,
        lv_color_black(),
        0);

    AmsState &state =
        AmsService::getState();

    for (int i = 0; i < 5; i++)
    {
        cards[i].create(
            contentContainer,
            &state.slots[i]);

        lv_obj_align(
            cards[i].getRoot(),
            LV_ALIGN_TOP_LEFT,
            3 + (63 * i),
            5);
    }

    // ==========================
    // SETTINGS BUTTON
    // ==========================

    settingsButton =
        lv_btn_create(contentContainer);

    lv_obj_remove_style_all(
        settingsButton);

    lv_obj_set_size(
        settingsButton,
        20,
        20);

    lv_obj_align(
        settingsButton,
        LV_ALIGN_BOTTOM_RIGHT,
        -5,
        -5);

    lv_obj_set_style_border_width(
        settingsButton,
        2,
        0);

    lv_obj_set_style_border_color(
        settingsButton,
        lv_color_hex(0x666666),
        0);
    // #444444

    lv_obj_set_style_bg_opa(
        settingsButton,
        LV_OPA_TRANSP,
        0);

    lv_obj_set_style_radius(
        settingsButton,
        LV_RADIUS_CIRCLE,
        0);

    lv_obj_t *settingsLabel =
        lv_label_create(settingsButton);

    lv_label_set_text(
        settingsLabel,
        LV_SYMBOL_SETTINGS);

    lv_obj_set_style_text_color(
        settingsLabel,
        lv_color_hex(0x666666),
        0);

    lv_obj_center(settingsLabel);

    lv_obj_add_event_cb(
        settingsButton,
        onSettingsClick,
        LV_EVENT_CLICKED,
        NULL);

    // ==========================
    // STAGING CONTAINER
    // ==========================

    stagingContainer =
        lv_obj_create(contentContainer);

    lv_obj_remove_style_all(stagingContainer);
    lv_obj_clear_flag(stagingContainer, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_size(
        stagingContainer,
        189,
        77);

    lv_obj_align(
        stagingContainer,
        LV_ALIGN_BOTTOM_LEFT,
        4,
        -4);

    lv_obj_set_style_bg_opa(stagingContainer, LV_OPA_COVER, 0);

    lv_obj_set_style_border_width(stagingContainer, 1, 0);

    lv_obj_set_style_border_color(stagingContainer, lv_color_hex(0x404040), 0);

    // lv_obj_set_style_radius(stagingContainer, 6, 0);

    lv_obj_set_style_bg_color(stagingContainer, lv_color_hex(0x151515), 0);

    lv_obj_add_flag(stagingContainer, LV_OBJ_FLAG_CLICKABLE);

    lv_obj_add_event_cb(
        stagingContainer,
        onStagingClick,
        LV_EVENT_CLICKED,
        this);

    // HEADER

    stagingHeaderLabel = lv_label_create(stagingContainer);

    lv_obj_set_style_text_font(stagingHeaderLabel, &lv_font_montserrat_14, 0);
    lv_obj_set_width(stagingHeaderLabel, 173);
    lv_label_set_long_mode(stagingHeaderLabel, LV_LABEL_LONG_SCROLL);
    lv_obj_align(stagingHeaderLabel, LV_ALIGN_TOP_LEFT, 8, 2);
    lv_label_set_text(stagingHeaderLabel, "TAG has been scanned! Insert spool into AMS or TAP for actions");

    // TITLE

    stagingTitleLabel = lv_label_create(stagingContainer);
    lv_obj_set_style_text_font(stagingTitleLabel, &lv_font_montserrat_16, 0);

    lv_obj_set_width(stagingTitleLabel, 173);

    lv_label_set_long_mode(
        stagingTitleLabel,
        LV_LABEL_LONG_SCROLL);

    lv_obj_align(
        stagingTitleLabel,
        LV_ALIGN_LEFT_MID,
        8,
        -2);

    // ID

    stagingIdLabel =
        lv_label_create(
            stagingContainer);

    lv_obj_align(
        stagingIdLabel,
        LV_ALIGN_BOTTOM_LEFT,
        8,
        -6);

    // WEIGHT

    stagingWeightLabel =
        lv_label_create(
            stagingContainer);

    lv_obj_set_style_text_font(
        stagingWeightLabel,
        &lv_font_montserrat_16,
        0);

    lv_obj_align(
        stagingWeightLabel,
        LV_ALIGN_BOTTOM_RIGHT,
        -10,
        -6);

    // ==========================
    // INFO LABELS
    // ==========================

    infoWifiLabel =
        lv_label_create(
            stagingContainer);

    lv_obj_align(
        infoWifiLabel,
        LV_ALIGN_TOP_LEFT,
        8,
        8);

    lv_obj_set_style_text_color(
        infoWifiLabel,
        lv_color_white(),
        0);

    infoAmsLabel =
        lv_label_create(
            stagingContainer);

    lv_obj_align(
        infoAmsLabel,
        LV_ALIGN_TOP_RIGHT,
        -8,
        8);

    lv_obj_set_style_text_color(
        infoAmsLabel,
        lv_color_hex(0x4CAF50),
        0);

    infoTempLabel =
        lv_label_create(
            stagingContainer);

    lv_obj_align(
        infoTempLabel,
        LV_ALIGN_BOTTOM_LEFT,
        8,
        -8);

    lv_obj_set_style_text_color(
        infoTempLabel,
        lv_color_hex(0xBBBBBB),
        0);

    infoHumidityLabel =
        lv_label_create(
            stagingContainer);

    lv_obj_align(
        infoHumidityLabel,
        LV_ALIGN_BOTTOM_RIGHT,
        -8,
        -8);

    lv_obj_set_style_text_color(
        infoHumidityLabel,
        lv_color_hex(0xBBBBBB),
        0);

    // ==========================
    // EDOL LOGO
    // ==========================

    lv_obj_t *logoContainer = lv_obj_create(contentContainer);
    lv_obj_remove_style_all(logoContainer);

    lv_obj_set_size(logoContainer,
                    92,
                    44);

    lv_obj_align(
        logoContainer,
        LV_ALIGN_BOTTOM_RIGHT,
        -22,
        -20);

    lv_obj_t *logo = lv_obj_create(logoContainer);
    lv_obj_remove_style_all(logo);

    lv_obj_set_size(logo,
                    44,
                    44);

    lv_obj_align(
        logo,
        LV_ALIGN_LEFT_MID,
        0,
        0);

    lv_obj_set_style_radius(logo, 18, 0);
    lv_obj_set_style_bg_opa(logo, LV_OPA_COVER, 0);
    lv_obj_set_style_bg_color(logo, lv_color_hex(0x257cc4), 0); // #257cc4

    //
    // inner cut
    //

    lv_obj_t *cut = lv_obj_create(logo);
    lv_obj_remove_style_all(cut);

    lv_obj_set_size(
        cut,
        50,
        28);

    lv_obj_align(
        cut,
        LV_ALIGN_LEFT_MID,
        8,
        0);

    lv_obj_set_style_radius(
        cut,
        10,
        0);

    lv_obj_set_style_bg_opa(
        cut,
        LV_OPA_COVER,
        0);

    lv_obj_set_style_bg_color(
        cut,
        lv_color_black(),
        0);

    //
    // horizontal line
    //

    lv_obj_t *line = lv_obj_create(logo);
    lv_obj_remove_style_all(line);
    lv_obj_set_size(
        line,
        38,
        4);

    lv_obj_align(
        line,
        LV_ALIGN_LEFT_MID,
        0,
        0);

    lv_obj_set_style_radius(line, LV_RADIUS_CIRCLE, 0);
    lv_obj_set_style_bg_opa(line, LV_OPA_COVER, 0);
    lv_obj_set_style_bg_color(line,
                              lv_color_hex(0x257cc4),
                              0);

    //
    // center dot
    //

    lv_obj_t *dot = lv_obj_create(logo);
    lv_obj_remove_style_all(dot);
    lv_obj_set_size(dot,
                    10,
                    10);

    lv_obj_align(
        dot,
        LV_ALIGN_LEFT_MID,
        15,
        0);

    lv_obj_set_style_radius(dot, LV_RADIUS_CIRCLE, 0);
    lv_obj_set_style_bg_opa(dot, LV_OPA_COVER, 0);
    lv_obj_set_style_bg_color(dot, lv_color_hex(0x257cc4), 0);

    lv_obj_t *dot2 = lv_obj_create(dot);
    lv_obj_remove_style_all(dot2);
    lv_obj_set_size(dot2,
                    6,
                    6);
    lv_obj_center(dot2);

    lv_obj_set_style_radius(dot2, LV_RADIUS_CIRCLE, 0);
    lv_obj_set_style_bg_opa(dot2, LV_OPA_COVER, 0);
    lv_obj_set_style_bg_color(dot2, lv_color_black(), 0);

    //
    // Text EDOL
    //

    lv_obj_t *title = lv_label_create(logoContainer);

    lv_label_set_text(title, "EDOL");

    lv_obj_set_style_text_color(
        title,
        lv_color_white(),
        0);

    lv_obj_set_style_text_font(
        title,
        &lv_font_montserrat_16,
        0);

    lv_obj_align(
        title,
        LV_ALIGN_RIGHT_MID,
        0,
        0);

    // ==========================
    // SLOT MODAL
    // ==========================

    slotModal = lv_obj_create(root);

    lv_obj_set_size(
        slotModal,
        280,
        180);

    lv_obj_clear_flag(
        slotModal,
        LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_center(slotModal);

    lv_obj_set_style_bg_color(
        slotModal,
        lv_color_hex(0x444444),
        0);

    lv_obj_set_style_border_width(
        slotModal,
        2,
        0);

    lv_obj_set_style_border_color(
        slotModal,
        lv_color_hex(0x999999),
        0);

    lv_obj_add_flag(
        slotModal,
        LV_OBJ_FLAG_HIDDEN);

    lv_obj_t *modalTitle =
        lv_label_create(
            slotModal);

    lv_label_set_text(
        modalTitle,
        "Choose slot");

    lv_obj_set_style_text_color(
        modalTitle,
        lv_color_white(),
        0);

    lv_obj_set_style_text_font(
        modalTitle,
        &lv_font_montserrat_16,
        0);

    lv_obj_align(
        modalTitle,
        LV_ALIGN_TOP_MID,
        0,
        -3);

    const char *labels[5] =
        {
            "A1",
            "A2",
            "A3",
            "A4",
            "EXT"};

    const uint8_t slots[5] =
        {
            0,
            1,
            2,
            3,
            254};

    for (int i = 0; i < 5; i++)
    {
        lv_obj_t *button =
            lv_btn_create(
                slotModal);

        int top = 30;
        int left = -2 + (i * 65);
        int width = 60;
        int height = 80;

        if (i == 4)
        {
            top = 120;
            left = -2;
            width = 125;
            height = 30;
        }

        lv_obj_set_size(
            button,
            width,
            height);

        lv_obj_align(
            button,
            LV_ALIGN_TOP_LEFT,
            left,
            top);

        lv_obj_set_user_data(
            button,
            (void *)(uintptr_t)slots[i]);

        lv_obj_add_event_cb(
            button,
            onSlotClick,
            LV_EVENT_CLICKED,
            this);

        lv_obj_t *label =
            lv_label_create(
                button);

        lv_label_set_text(
            label,
            labels[i]);

        lv_obj_center(label);
    }

    lv_obj_t *cancelButton =
        lv_btn_create(
            slotModal);

    lv_obj_set_size(
        cancelButton,
        90,
        30);

    lv_obj_align(
        cancelButton,
        LV_ALIGN_BOTTOM_RIGHT,
        -4,
        0);

    lv_obj_add_event_cb(
        cancelButton,
        onCancelSlotClick,
        LV_EVENT_CLICKED,
        this);

    lv_obj_t *cancelLabel =
        lv_label_create(
            cancelButton);

    lv_label_set_text(
        cancelLabel,
        "CANCEL");

    lv_obj_center(
        cancelLabel);

    // ==========================
    // TOAST
    // ==========================

    toast = lv_label_create(root);

    lv_obj_set_style_bg_opa(
        toast,
        LV_OPA_COVER,
        0);

    lv_obj_set_style_bg_color(
        toast,
        lv_color_hex(0x2a5e20), // #2a5e20
        0);

    lv_obj_set_style_radius(
        toast,
        6,
        0);

    lv_obj_set_style_pad_all(
        toast,
        10,
        0);

    lv_obj_set_style_text_color(
        toast,
        lv_color_white(),
        0);

    lv_obj_align(
        toast,
        LV_ALIGN_CENTER,
        0,
        0);

    lv_obj_add_flag(
        toast,
        LV_OBJ_FLAG_HIDDEN);

    activeScreen = this;

    refreshTimer =
        lv_timer_create(
            refreshCards,
            1000,
            nullptr);

    // refreshCards(refreshTimer);
}

void HomeScreen::destroy()
{
    if (refreshTimer)
    {
        lv_timer_del(refreshTimer);
        refreshTimer = nullptr;
    }
    activeScreen = nullptr;
    lv_obj_del(root);
}

void HomeScreen::onSettingsClick(
    lv_event_t *event)
{
    Navigation::push(new SettingsScreen());
}

void HomeScreen::refreshNow()
{
    if (!activeScreen)
    {
        return;
    }
    // lv_timer_ready(activeScreen->refreshTimer);
}

void HomeScreen::refreshCards(lv_timer_t *timer)
{
    if (!activeScreen)
    {
        return;
    }
    HomeScreen *screen = activeScreen;

    if (
        screen->slotModal &&
        !lv_obj_has_flag(
            screen->slotModal,
            LV_OBJ_FLAG_HIDDEN))
    {
        StagingService::keepAlive();
    }

    AmsState &state = AmsService::getState();

    if (state.loaded)
    {
        for (int i = 0; i < 5; i++)
        {
            screen->cards[i].setSpool(&state.slots[i]);
        }
    }

    if (!StagingService::hasSpool())
    {
        lv_obj_clear_flag(
            screen->stagingContainer,
            LV_OBJ_FLAG_HIDDEN);

        lv_obj_add_flag(
            screen->stagingHeaderLabel,
            LV_OBJ_FLAG_HIDDEN);

        lv_obj_add_flag(
            screen->stagingTitleLabel,
            LV_OBJ_FLAG_HIDDEN);

        lv_obj_add_flag(
            screen->stagingIdLabel,
            LV_OBJ_FLAG_HIDDEN);

        lv_obj_add_flag(
            screen->stagingWeightLabel,
            LV_OBJ_FLAG_HIDDEN);

        lv_obj_clear_flag(
            screen->infoWifiLabel,
            LV_OBJ_FLAG_HIDDEN);

        lv_obj_clear_flag(
            screen->infoAmsLabel,
            LV_OBJ_FLAG_HIDDEN);

        lv_obj_clear_flag(
            screen->infoTempLabel,
            LV_OBJ_FLAG_HIDDEN);

        lv_obj_clear_flag(
            screen->infoHumidityLabel,
            LV_OBJ_FLAG_HIDDEN);

        lv_obj_set_style_bg_color(
            screen->stagingContainer,
            lv_color_hex(0x151515),
            0);

        lv_label_set_text(
            screen->infoWifiLabel,
            "WiFi Connected");

        lv_label_set_text(
            screen->infoAmsLabel,
            "AMS");

        snprintf(
            screen->stagingTitle,
            sizeof(screen->stagingTitle),
            "Temp: %.1f\xC2\xB0"
            "C",
            state.temperature);

        lv_label_set_text(
            screen->infoTempLabel,
            screen->stagingTitle);

        snprintf(
            screen->stagingWeight,
            sizeof(screen->stagingWeight),
            "Hum: %d%%",
            state.humidity);

        lv_label_set_text(
            screen->infoHumidityLabel,
            screen->stagingWeight);

        return;
    }

    lv_obj_add_flag(
        screen->infoWifiLabel,
        LV_OBJ_FLAG_HIDDEN);

    lv_obj_add_flag(
        screen->infoAmsLabel,
        LV_OBJ_FLAG_HIDDEN);

    lv_obj_add_flag(
        screen->infoTempLabel,
        LV_OBJ_FLAG_HIDDEN);

    lv_obj_add_flag(
        screen->infoHumidityLabel,
        LV_OBJ_FLAG_HIDDEN);

    lv_obj_clear_flag(
        screen->stagingHeaderLabel,
        LV_OBJ_FLAG_HIDDEN);

    lv_obj_clear_flag(
        screen->stagingTitleLabel,
        LV_OBJ_FLAG_HIDDEN);

    lv_obj_clear_flag(
        screen->stagingIdLabel,
        LV_OBJ_FLAG_HIDDEN);

    lv_obj_clear_flag(
        screen->stagingWeightLabel,
        LV_OBJ_FLAG_HIDDEN);

    Spool &spool = StagingService::getSpool();

    lv_color_t textColor =
        isDarkColor(
            spool.color.c_str())
            ? lv_color_white()
            : lv_color_black();

    lv_obj_clear_flag(
        screen->stagingContainer,
        LV_OBJ_FLAG_HIDDEN);

    lv_obj_set_style_bg_color(
        screen->stagingContainer,
        hexToColor(spool.color.c_str()),
        0);

    lv_obj_set_style_text_color(screen->stagingHeaderLabel, textColor, 0);
    lv_obj_set_style_text_color(screen->stagingTitleLabel, textColor, 0);
    lv_obj_set_style_text_color(screen->stagingIdLabel, textColor, 0);
    lv_obj_set_style_text_color(screen->stagingWeightLabel, textColor, 0);

    snprintf(
        screen->stagingTitle,
        sizeof(screen->stagingTitle),
        "%s %s %s",
        spool.vendor.c_str(),
        spool.material.c_str(),
        spool.brand.c_str());

    lv_label_set_text(
        screen->stagingTitleLabel,
        screen->stagingTitle);

    snprintf(
        screen->stagingId,
        sizeof(screen->stagingId),
        "ID %d",
        spool.id);

    lv_label_set_text(
        screen->stagingIdLabel,
        screen->stagingId);

    char weight[16];

    snprintf(
        screen->stagingWeight,
        sizeof(screen->stagingWeight),
        "%dg",
        spool.weight);

    lv_label_set_text(
        screen->stagingWeightLabel,
        screen->stagingWeight);
}

void HomeScreen::onStagingClick(
    lv_event_t *event)
{
    if (!StagingService::hasSpool())
    {
        return;
    }

    auto *screen =
        static_cast<HomeScreen *>(
            lv_event_get_user_data(event));

    lv_obj_clear_flag(
        screen->slotModal,
        LV_OBJ_FLAG_HIDDEN);
}

void HomeScreen::onCancelSlotClick(
    lv_event_t *event)
{
    auto *screen =
        static_cast<HomeScreen *>(
            lv_event_get_user_data(event));

    lv_obj_add_flag(
        screen->slotModal,
        LV_OBJ_FLAG_HIDDEN);

    StagingService::clear();
}

void HomeScreen::onSlotClick(
    lv_event_t *event)
{
    auto *screen =
        static_cast<HomeScreen *>(
            lv_event_get_user_data(event));

    uint8_t slot =
        (uint8_t)(uintptr_t)
            lv_obj_get_user_data(
                lv_event_get_target(event));

    int spoolId =
        StagingService::getSpool().id;

    StagingService::assignToSlot(
        slot);

    lv_obj_add_flag(
        screen->slotModal,
        LV_OBJ_FLAG_HIDDEN);

    if (slot == 254)
    {
        snprintf(
            screen->toastText,
            sizeof(screen->toastText),
            "Put spool ID %d into EXT tray",
            spoolId);
    }
    else
    {
        snprintf(
            screen->toastText,
            sizeof(screen->toastText),
            "Put spool ID %d into AMS slot %d",
            spoolId,
            slot + 1);
    }

    lv_label_set_text(
        screen->toast,
        screen->toastText);

    lv_obj_clear_flag(
        screen->toast,
        LV_OBJ_FLAG_HIDDEN);

    if (screen->toastTimer)
    {
        lv_timer_del(
            screen->toastTimer);
    }

    screen->toastTimer =
        lv_timer_create(
            hideToast,
            10000,
            screen);
}

void HomeScreen::hideToast(
    lv_timer_t *timer)
{
    auto *screen =
        static_cast<HomeScreen *>(
            timer->user_data);

    lv_obj_add_flag(
        screen->toast,
        LV_OBJ_FLAG_HIDDEN);

    lv_timer_del(timer);

    screen->toastTimer = nullptr;
}