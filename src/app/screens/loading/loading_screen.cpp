#include "loading_screen.h"

#include "../../app.h"

#include "../../navigation/navigation.h"
#include "../settings/settings_screen.h"

void LoadingScreen::create()
{
    root = lv_obj_create(
        lv_scr_act());

    lv_obj_remove_style_all(
        root);

    lv_obj_set_size(
        root,
        LV_PCT(100),
        LV_PCT(100));

    lv_obj_set_style_bg_color(
        root,
        lv_color_black(),
        0);

    lv_obj_set_style_bg_opa(
        root,
        LV_OPA_COVER,
        0);

    // ==========================
    // LOGO
    // ==========================
    lv_obj_t *logoContainer =
        lv_obj_create(root);

    lv_obj_remove_style_all(
        logoContainer);

    lv_obj_set_size(
        logoContainer,
        220,
        80);

    lv_obj_align(
        logoContainer,
        LV_ALIGN_CENTER,
        20,
        -20);

    //
    // E SYMBOL
    //

    lv_obj_t *symbol =
        lv_obj_create(
            logoContainer);

    lv_obj_remove_style_all(
        symbol);

    lv_obj_set_size(
        symbol,
        56,
        56);

    lv_obj_align(
        symbol,
        LV_ALIGN_LEFT_MID,
        0,
        0);

    lv_obj_set_style_radius(
        symbol,
        18,
        0);

    lv_obj_set_style_bg_opa(
        symbol,
        LV_OPA_COVER,
        0);

    lv_obj_set_style_bg_color(
        symbol,
        lv_color_hex(0x4F7CFF),
        0);

    //
    // inner cut
    //

    lv_obj_t *cut =
        lv_obj_create(symbol);

    lv_obj_remove_style_all(cut);

    lv_obj_set_size(
        cut,
        57,
        34);

    lv_obj_align(
        cut,
        LV_ALIGN_LEFT_MID,
        11,
        0);

    lv_obj_set_style_radius(
        cut,
        12,
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
    // center dot
    //

    lv_obj_t *dot =
        lv_obj_create(symbol);

    lv_obj_remove_style_all(dot);

    lv_obj_set_size(
        dot,
        10,
        10);

    lv_obj_center(dot);

    lv_obj_set_style_radius(
        dot,
        LV_RADIUS_CIRCLE,
        0);

    lv_obj_set_style_bg_opa(
        dot,
        LV_OPA_COVER,
        0);

    lv_obj_set_style_bg_color(
        dot,
        lv_color_hex(0x4F7CFF),
        0);

    //
    // horizontal line
    //

    lv_obj_t *line =
        lv_obj_create(symbol);

    lv_obj_remove_style_all(line);

    lv_obj_set_size(
        line,
        42,
        4);

    lv_obj_align(
        line,
        LV_ALIGN_CENTER,
        0,
        0);

    lv_obj_set_style_radius(
        line,
        LV_RADIUS_CIRCLE,
        0);

    lv_obj_set_style_bg_opa(
        line,
        LV_OPA_COVER,
        0);

    lv_obj_set_style_bg_color(
        line,
        lv_color_hex(0x4F7CFF),
        0);

    //
    // EDOL TEXT
    //

    lv_obj_t *title =
        lv_label_create(
            logoContainer);

    lv_label_set_text(
        title,
        "EDOL");

    lv_obj_set_style_text_color(
        title,
        lv_color_white(),
        0);

    lv_obj_set_style_text_font(
        title,
        &lv_font_montserrat_28,
        0);

    lv_obj_align(
        title,
        LV_ALIGN_LEFT_MID,
        72,
        0);

    // ==========================
    // STATUS
    // ==========================

    statusLabel =
        lv_label_create(root);

    lv_label_set_text(
        statusLabel,
        "Booting...");

    lv_obj_set_style_text_color(
        statusLabel,
        lv_color_hex(0x888888),
        0);

    lv_obj_align(
        statusLabel,
        LV_ALIGN_CENTER,
        0,
        35);

    // ==========================
    // SETTINGS BUTTON
    // ==========================

    lv_obj_t *settingsButton =
        lv_btn_create(root);

    lv_obj_remove_style_all(
        settingsButton);

    lv_obj_set_size(
        settingsButton,
        30,
        30);

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
        lv_color_white(),
        0);

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
        lv_color_white(),
        0);

    lv_obj_center(settingsLabel);

    lv_obj_add_event_cb(
        settingsButton,
        onSettingsClick,
        LV_EVENT_CLICKED,
        NULL);
}

void LoadingScreen::destroy()
{
    if (root)
    {
        lv_obj_del(root);
        root = nullptr;
    }
}

void LoadingScreen::setStatus(
    const char *text)
{
    lv_label_set_text(
        statusLabel,
        text);
}

void LoadingScreen::onSettingsClick(
    lv_event_t *event)
{
    App::loadingScreen = nullptr;

    Navigation::replace(
        new SettingsScreen());
}