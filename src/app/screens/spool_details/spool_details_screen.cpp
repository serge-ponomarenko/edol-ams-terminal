#include "spool_details_screen.h"

#include "../../navigation/navigation.h"

#include "../../services/nfc/nfc_service.h"
#include "../../../../src/utils/utils.h"

SpoolDetailsScreen::SpoolDetailsScreen(
    Spool *spool)
{
    this->spool = spool;
}

void SpoolDetailsScreen::create()
{
    root = lv_obj_create(
        lv_scr_act());

    lv_obj_remove_style_all(root);

    lv_obj_set_size(
        root,
        LV_PCT(100),
        LV_PCT(100));

    lv_color_t textColor =
        isDarkColor(spool->color.c_str())
            ? lv_color_white()
            : lv_color_black();

    lv_obj_set_style_bg_opa(
        root,
        LV_OPA_COVER,
        0);

    lv_obj_set_style_bg_color(
        root,
        hexToColor(spool->color.c_str()),
        0);

    // ==========================
    // SLOT
    // ==========================

    lv_obj_t *slotContainer =
        lv_obj_create(root);

    lv_obj_remove_style_all(
        slotContainer);

    lv_obj_set_size(
        slotContainer,
        70,
        28);

    lv_obj_set_style_radius(
        slotContainer,
        6,
        0);

    if (spool->isActive)
    {

        lv_obj_set_style_bg_opa(
            slotContainer,
            LV_OPA_COVER,
            0);

        lv_obj_set_style_bg_color(
            slotContainer,
            lv_color_white(),
            0);

        lv_obj_set_style_border_width(
            slotContainer,
            2,
            0);

        lv_obj_set_style_border_color(
            slotContainer,
            lv_color_black(),
            0);
    }

    lv_obj_align(
        slotContainer,
        LV_ALIGN_TOP_LEFT,
        5,
        10);

    lv_obj_t *slot =
        lv_label_create(slotContainer);

    char slot_text[10];

    sprintf(
        slot_text,
        "Slot: %s",
        spool->slot.c_str());

    lv_label_set_text(
        slot,
        slot_text);

    lv_obj_set_style_text_font(
        slot,
        &lv_font_montserrat_16,
        0);

    lv_obj_set_style_text_color(
        slot,
        spool->isActive
            ? lv_color_black()
            : textColor,
        0);

    lv_obj_center(slot);

    // ==========================
    // MATERIAL
    // ==========================

    lv_obj_t *material =
        lv_label_create(root);

    char material_text[25];

    sprintf(
        material_text,
        "Material: %s",
        spool->material.c_str());

    lv_label_set_text(
        material,
        material_text);

    lv_obj_set_style_text_font(
        material,
        &lv_font_montserrat_16,
        0);

    lv_obj_set_style_text_color(
        material,
        textColor,
        0);

    lv_obj_align(
        material,
        LV_ALIGN_TOP_LEFT,
        10,
        37); // +25

    // ==========================
    // BRAND
    // ==========================
    lv_obj_t *brand =
        lv_label_create(root);

    char brand_text[30];

    sprintf(
        brand_text,
        "Brand: %s",
        spool->brand.c_str());

    lv_label_set_text(
        brand,
        brand_text);

    lv_obj_set_style_text_font(
        brand,
        &lv_font_montserrat_16,
        0);

    lv_obj_set_style_text_color(
        brand,
        textColor,
        0);

    lv_obj_align(
        brand,
        LV_ALIGN_TOP_LEFT,
        10,
        57);

    // ==========================
    // VENDOR
    // ==========================
    lv_obj_t *vendor =
        lv_label_create(root);

    char vendor_text[30];

    sprintf(
        vendor_text,
        "Vendor: %s",
        spool->vendor.c_str());

    lv_label_set_text(
        vendor,
        vendor_text);

    lv_obj_set_style_text_font(
        vendor,
        &lv_font_montserrat_16,
        0);

    lv_obj_set_style_text_color(
        vendor,
        textColor,
        0);

    lv_obj_align(
        vendor,
        LV_ALIGN_TOP_LEFT,
        11,
        77);

    // ==========================
    // ID
    // ==========================
    lv_obj_t *id =
        lv_label_create(root);

    char id_text[30];

    sprintf(
        id_text,
        "ID: %d",
        spool->id);

    lv_label_set_text(
        id,
        id_text);

    lv_obj_set_style_text_font(
        id,
        &lv_font_montserrat_16,
        0);

    lv_obj_set_style_text_color(
        id,
        textColor,
        0);

    lv_obj_align(
        id,
        LV_ALIGN_TOP_LEFT,
        11,
        97);

    // ==========================
    // WEIGHT
    // ==========================

    lv_obj_t *weightCircle =
        lv_obj_create(root);

    lv_obj_remove_style_all(
        weightCircle);

    lv_obj_set_size(
        weightCircle,
        120,
        120);

    lv_obj_set_style_bg_opa(
        weightCircle,
        LV_OPA_TRANSP,
        0);

    lv_obj_set_style_border_width(
        weightCircle,
        3,
        0);

    lv_obj_set_style_border_color(
        weightCircle,
        textColor,
        0);

    lv_obj_set_style_radius(
        weightCircle,
        LV_RADIUS_CIRCLE,
        0);

    lv_obj_align(
        weightCircle,
        LV_ALIGN_TOP_RIGHT,
        -3,
        10);

    lv_obj_t *weight =
        lv_label_create(weightCircle);

    char weightText[32];

    sprintf(
        weightText,
        "%d",
        spool->weight);

    lv_label_set_text(
        weight,
        weightText);

    lv_obj_set_style_text_font(
        weight,
        &lv_font_montserrat_28,
        0);

    lv_obj_set_style_text_color(
        weight,
        textColor,
        0);

    lv_obj_center(weight);

    lv_obj_t *grams =
        lv_label_create(weightCircle);

    lv_label_set_text(
        grams,
        "g");

    lv_obj_set_style_text_font(
        grams,
        &lv_font_montserrat_16,
        0);

    lv_obj_set_style_text_color(
        grams,
        textColor,
        0);

    lv_obj_align(
        grams,
        LV_ALIGN_BOTTOM_MID,
        0,
        -14);

    // ==========================
    // BACK BUTTON
    // ==========================

    backButton =
        lv_btn_create(root);

    lv_obj_remove_style_all(backButton);

    lv_obj_set_style_border_width(
        backButton,
        2,
        0);

    lv_obj_set_style_text_color(
        backButton,
        textColor,
        0);

    lv_obj_set_style_border_color(
        backButton,
        textColor,
        0);

    lv_obj_set_style_bg_opa(
        backButton,
        LV_OPA_TRANSP,
        0);

    lv_obj_set_size(
        backButton,
        80,
        32);

    lv_obj_align(
        backButton,
        LV_ALIGN_BOTTOM_LEFT,
        10,
        -10);

    lv_obj_t *label =
        lv_label_create(backButton);

    lv_label_set_text(
        label,
        "< BACK");

    lv_obj_center(label);

    lv_obj_add_event_cb(
        backButton,
        onBackClick,
        LV_EVENT_CLICKED,
        NULL);

    // ==========================
    // ENCODE BUTTON
    // ==========================

    lv_obj_t *encodeButton =
        lv_btn_create(root);

    lv_obj_remove_style_all(
        encodeButton);

    lv_obj_set_style_border_width(
        encodeButton,
        2,
        0);

    lv_obj_set_style_border_color(
        encodeButton,
        textColor,
        0);

    lv_obj_set_style_bg_opa(
        encodeButton,
        LV_OPA_TRANSP,
        0);

    lv_obj_set_style_text_color(
        encodeButton,
        textColor,
        0);

    lv_obj_set_size(
        encodeButton,
        90,
        32);

    lv_obj_align(
        encodeButton,
        LV_ALIGN_BOTTOM_RIGHT,
        -10,
        -50);

    lv_obj_t *encodeLabel =
        lv_label_create(encodeButton);

    lv_label_set_text(
        encodeLabel,
        "ENCODE");

    lv_obj_center(encodeLabel);

    lv_obj_add_event_cb(
        encodeButton,
        onEncodeClick,
        LV_EVENT_CLICKED,
        this);

    // ==========================
    // ERASE BUTTON
    // ==========================

    lv_obj_t *eraseButton =
        lv_btn_create(root);

    lv_obj_remove_style_all(
        eraseButton);

    lv_obj_set_style_border_width(
        eraseButton,
        2,
        0);

    lv_obj_set_style_border_color(
        eraseButton,
        lv_color_hex(0xFF5252),
        0);

    lv_obj_set_style_bg_opa(
        eraseButton,
        LV_OPA_TRANSP,
        0);

    lv_obj_set_style_text_color(
        eraseButton,
        lv_color_hex(0xFF5252),
        0);

    lv_obj_set_size(
        eraseButton,
        90,
        32);

    lv_obj_align(
        eraseButton,
        LV_ALIGN_BOTTOM_RIGHT,
        -10,
        -10);

    lv_obj_t *eraseLabel =
        lv_label_create(eraseButton);

    lv_label_set_text(
        eraseLabel,
        "ERASE");

    lv_obj_center(eraseLabel);

    lv_obj_add_event_cb(
        eraseButton,
        onEraseClick,
        LV_EVENT_CLICKED,
        this);

    // ==========================
    // NFC MODAL
    // ==========================

    nfcModal = lv_obj_create(root);

    lv_obj_set_size(
        nfcModal,
        180,
        120);

    lv_obj_center(nfcModal);

    lv_obj_add_flag(
        nfcModal,
        LV_OBJ_FLAG_HIDDEN);

    nfcModalText = lv_label_create(nfcModal);

    lv_label_set_text(
        nfcModalText,
        "PLACE NFC TAG");

    lv_obj_align(
        nfcModalText,
        LV_ALIGN_CENTER,
        0,
        -20);

    nfcCancelButton = lv_btn_create(nfcModal);

    lv_obj_set_size(
        nfcCancelButton,
        80,
        32);

    lv_obj_align(
        nfcCancelButton,
        LV_ALIGN_BOTTOM_MID,
        0,
        -10);

    lv_obj_t *cancelLabel =
        lv_label_create(
            nfcCancelButton);

    lv_label_set_text(
        cancelLabel,
        "CANCEL");

    lv_obj_center(cancelLabel);

    lv_obj_add_event_cb(
        nfcCancelButton,
        onCancelNfcClick,
        LV_EVENT_CLICKED,
        this);

    // ==========================
    // UPDATE TIMER
    // ==========================

    updateTimer =
        lv_timer_create(
            onUpdateTimer,
            100,
            this);
}

void SpoolDetailsScreen::destroy()
{
    if (updateTimer)
    {
        lv_timer_del(updateTimer);
    }

    lv_obj_del(root);
}

void SpoolDetailsScreen::onBackClick(
    lv_event_t *event)
{
    Navigation::back();
}

void SpoolDetailsScreen::onEncodeClick(
    lv_event_t *event)
{
    auto *screen =
        static_cast<SpoolDetailsScreen *>(
            lv_event_get_user_data(event));

    NfcService::startWrite(screen->spool->id);

    Serial.print(F("NFC WRITE START: "));

    Serial.println(screen->spool->id);
}

void SpoolDetailsScreen::onEraseClick(
    lv_event_t *event)
{
    NfcService::startWrite(-1);

    Serial.println(
        F("NFC ERASE START"));
}

void SpoolDetailsScreen::onUpdateTimer(
    lv_timer_t *timer)
{
    auto *screen =
        static_cast<SpoolDetailsScreen *>(
            timer->user_data);

    auto state = NfcService::getState();

    bool visible = state != NfcWriteState::IDLE;

    if (visible)
    {
        lv_obj_clear_flag(
            screen->nfcModal,
            LV_OBJ_FLAG_HIDDEN);
    }
    else
    {
        lv_obj_add_flag(
            screen->nfcModal,
            LV_OBJ_FLAG_HIDDEN);

        return;
    }

    switch (state)
    {
    case NfcWriteState::WAITING_FOR_TAG:
        lv_obj_clear_state(screen->nfcCancelButton, LV_STATE_DISABLED);
        lv_label_set_text(screen->nfcModalText, "PLACE NFC TAG");
        break;

    case NfcWriteState::SUCCESS:
        lv_obj_add_state(screen->nfcCancelButton, LV_STATE_DISABLED);
        lv_label_set_text(screen->nfcModalText, "TAG WRITTEN");
        break;

    case NfcWriteState::ERROR:
        lv_obj_add_state(screen->nfcCancelButton, LV_STATE_DISABLED);
        lv_label_set_text(screen->nfcModalText, "WRITE FAILED");
        break;

    default:
        break;
    }
}

void SpoolDetailsScreen::onCancelNfcClick(lv_event_t *event)
{
    NfcService::cancel();
}