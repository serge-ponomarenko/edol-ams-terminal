#include "slot_card_v2.h"

#include "../../../app/navigation/navigation.h"
#include "../../../app/screens/spool_details/spool_details_screen.h"
#include "../../../../src/utils/utils.h"

void SlotCardV2::create(
    lv_obj_t *parent,
    Spool *spool)
{
    this->spool = spool;

    root = lv_obj_create(parent);

    lv_color_t textColor =
        isDarkColor(
            spool->color.c_str())
            ? lv_color_white()
            : lv_color_black();

    // ==========================
    // ROOT STYLE
    // ==========================

    lv_obj_remove_style_all(root);

    lv_obj_clear_flag(
        root,
        LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_size(
        root,
        62,
        150);

    lv_obj_set_style_bg_opa(
        root,
        LV_OPA_COVER,
        0);

    lv_obj_set_style_bg_color(
        root,
        hexToColor(spool->color.c_str()),
        0);

    lv_obj_set_style_border_width(
        root,
        1,
        0);

    lv_obj_set_style_border_color(
        root,
        lv_color_hex(0x555555),
        0);

    lv_obj_set_style_radius(
        root,
        0,
        0);

    lv_obj_set_style_pad_all(
        root,
        0,
        0);

    // ==========================
    // SLOT
    // ==========================

    slotContainer =
        lv_obj_create(root);

    lv_obj_remove_style_all(
        slotContainer);

    lv_obj_set_size(
        slotContainer,
        40,
        18);

    lv_obj_set_style_radius(
        slotContainer,
        4,
        0);

    lv_obj_align(
        slotContainer,
        LV_ALIGN_TOP_MID,
        0,
        3);

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
            1,
            0);

        lv_obj_set_style_border_color(
            slotContainer,
            lv_color_black(),
            0);
    }
    else
    {

        lv_obj_set_style_bg_opa(
            slotContainer,
            LV_OPA_TRANSP,
            0);

        lv_obj_set_style_border_width(
            slotContainer,
            0,
            0);
    }

    slotLabel =
        lv_label_create(slotContainer);

    lv_label_set_text(
        slotLabel,
        spool->slot.c_str());

    if (spool->isActive)
    {

        lv_obj_set_style_text_color(
            slotLabel,
            lv_color_black(),
            0);
    }
    else
    {

        lv_obj_set_style_text_color(
            slotLabel,
            textColor,
            0);
    }

    lv_obj_center(slotLabel);

    // ==========================
    // ID
    // ==========================

    lv_obj_t *idContainer =
        lv_obj_create(root);

    lv_obj_remove_style_all(
        idContainer);

    lv_obj_clear_flag(
        idContainer,
        LV_OBJ_FLAG_CLICKABLE);

    lv_obj_set_size(
        idContainer,
        52,
        18);

    lv_obj_set_style_bg_opa(
        idContainer,
        LV_OPA_COVER,
        0);

    lv_obj_set_style_bg_color(
        idContainer,
        lv_palette_main(LV_PALETTE_GREEN),
        0);

    lv_obj_set_style_border_width(
        idContainer,
        1,
        0);

    lv_obj_set_style_border_color(
        idContainer,
        lv_color_black(),
        0);

    lv_obj_set_style_radius(
        idContainer,
        4,
        0);

    lv_obj_align(
        idContainer,
        LV_ALIGN_TOP_MID,
        0,
        23);

    // ==========================
    // ID Label
    // ==========================

    idLabel =
        lv_label_create(idContainer);

    char idText[24];

    sprintf(
        idText,
        "%d",
        spool->id);

    lv_label_set_text(
        idLabel,
        idText);

    lv_obj_set_style_text_color(
        idLabel,
        lv_color_black(),
        0);

    lv_obj_center(idLabel);

    // ==========================
    // WEIGHT
    // ==========================

    weightCircle =
        lv_obj_create(root);

    lv_obj_remove_style_all(
        weightCircle);

    lv_obj_clear_flag(
        weightCircle,
        LV_OBJ_FLAG_CLICKABLE);

    lv_obj_set_size(
        weightCircle,
        55,
        55);

    lv_obj_set_style_bg_opa(
        weightCircle,
        LV_OPA_COVER,
        100);

    lv_obj_set_style_border_width(
        weightCircle,
        2,
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
        LV_ALIGN_CENTER,
        0,
        -2);

    // ==========================
    // WEIGHT Label
    // ==========================

    weightLabel =
        lv_label_create(weightCircle);

    char weightText[24];

    sprintf(
        weightText,
        "%d",
        spool->weight);

    lv_label_set_text(
        weightLabel,
        weightText);

    lv_obj_set_style_text_color(
        weightLabel,
        textColor,
        0);

    lv_obj_set_style_text_font(
        weightLabel,
        &lv_font_montserrat_16,
        0);

    lv_obj_center(weightLabel);

    weightUnitLabel =
        lv_label_create(weightCircle);

    lv_label_set_text(
        weightUnitLabel,
        "g");

    lv_obj_set_style_text_color(
        weightUnitLabel,
        textColor,
        0);

    lv_obj_set_style_text_font(
        weightUnitLabel,
        &lv_font_montserrat_14,
        0);

    lv_obj_align(
        weightUnitLabel,
        LV_ALIGN_BOTTOM_MID,
        0,
        -5);

    // ==========================
    // MATERIAL
    // ==========================

    materialLabel =
        lv_label_create(root);

    lv_label_set_long_mode(
        materialLabel,
        LV_LABEL_LONG_SCROLL);

    lv_obj_set_width(
        materialLabel,
        52);

    lv_obj_set_style_text_align(
        materialLabel,
        LV_TEXT_ALIGN_CENTER,
        0);

    lv_label_set_text(
        materialLabel,
        spool->material.c_str());

    lv_obj_set_style_text_color(
        materialLabel,
        textColor,
        0);

    lv_obj_align(
        materialLabel,
        LV_ALIGN_BOTTOM_MID,
        0,
        -22);

    // ==========================
    // BRAND
    // ==========================

    brandLabel =
        lv_label_create(root);

    lv_label_set_long_mode(
        brandLabel,
        LV_LABEL_LONG_SCROLL);

    lv_obj_set_width(
        brandLabel,
        52);

    lv_obj_set_style_text_align(
        brandLabel,
        LV_TEXT_ALIGN_CENTER,
        0);

    lv_label_set_text(
        brandLabel,
        spool->brand.c_str());

    lv_obj_set_style_text_color(
        brandLabel,
        textColor,
        0);

    lv_obj_align(
        brandLabel,
        LV_ALIGN_BOTTOM_MID,
        0,
        -4);

    setSpool(spool);

    lv_obj_add_event_cb(
        root,
        onClick,
        LV_EVENT_CLICKED,
        spool);
}

lv_obj_t *SlotCardV2::getRoot()
{
    return root;
}

void SlotCardV2::setSpool(
    Spool *spool)
{
    this->spool = spool;

    if (spool->isEmpty || (spool->slot.equals("EXT") && spool->material.isEmpty()))
    {
        lv_obj_set_style_bg_color(
            root,
            lv_color_hex(0x303030),
            0);

        // SLOT

        lv_label_set_text(
            slotLabel,
            spool->slot.c_str());

        lv_obj_set_style_bg_opa(
            slotContainer,
            LV_OPA_TRANSP,
            0);

        lv_obj_set_style_border_width(
            slotContainer,
            0,
            0);

        lv_obj_set_style_text_color(
            slotLabel,
            lv_color_white(),
            0);

        // ID

        lv_obj_add_flag(
            idLabel,
            LV_OBJ_FLAG_HIDDEN);

        // WEIGHT

        lv_obj_add_flag(
            weightCircle,
            LV_OBJ_FLAG_HIDDEN);

        // MATERIAL

        lv_label_set_text(
            materialLabel,
            "EMPTY");

        lv_obj_set_style_text_color(
            materialLabel,
            lv_color_hex(0xAAAAAA),
            0);

        // BRAND

        lv_label_set_text(
            brandLabel,
            "");

        lv_obj_clear_flag(
            root,
            LV_OBJ_FLAG_CLICKABLE);

        return;
    }

    if (!spool->isEmpty && spool->material.isEmpty())
    {
        lv_obj_set_style_bg_color(
            root,
            lv_color_hex(0xfc9f9f), // #fc9f9f
            0);

        // SLOT

        lv_label_set_text(
            slotLabel,
            spool->slot.c_str());

        lv_obj_set_style_bg_opa(
            slotContainer,
            LV_OPA_TRANSP,
            0);

        lv_obj_set_style_border_width(
            slotContainer,
            0,
            0);

        lv_obj_set_style_text_color(
            slotLabel,
            lv_color_hex(0x2e2828), // #2e2828
            0);

        // ID

        lv_obj_add_flag(
            idLabel,
            LV_OBJ_FLAG_HIDDEN);

        // WEIGHT

        lv_label_set_text(
            weightLabel,
            "???");

        lv_obj_set_style_text_color(
            weightLabel,
            lv_color_hex(0x2e2828),
            0);

        lv_label_set_text(
            weightUnitLabel,
            "");

        lv_obj_set_style_border_color(
            weightCircle,
            lv_color_hex(0x2e2828),
            0);

        // MATERIAL

        lv_label_set_text(
            materialLabel,
            "");

        lv_obj_set_style_text_color(
            materialLabel,
            lv_color_hex(0xAAAAAA),
            0);

        // BRAND

        lv_label_set_text(
            brandLabel,
            "");

        lv_obj_clear_flag(
            root,
            LV_OBJ_FLAG_CLICKABLE);

        return;
    }

    if (spool->id == 0 && spool->vendor.isEmpty())
    {
        lv_color_t textColor =
            isDarkColor(
                spool->color.c_str())
                ? lv_color_white()
                : lv_color_black();

        lv_obj_set_style_bg_color(
            root,
            hexToColor(
                spool->color.c_str()),
            0);

        // SLOT

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
                1,
                0);

            lv_obj_set_style_border_color(
                slotContainer,
                lv_color_black(),
                0);

            lv_obj_set_style_text_color(
                slotLabel,
                lv_color_black(),
                0);
        }
        else
        {

            lv_label_set_text(
                slotLabel,
                spool->slot.c_str());

            lv_obj_set_style_bg_opa(
                slotContainer,
                LV_OPA_TRANSP,
                0);

            lv_obj_set_style_border_width(
                slotContainer,
                0,
                0);

            lv_obj_set_style_text_color(
                slotLabel,
                textColor,
                0);
        }

        // ID

        lv_obj_add_flag(
            idLabel,
            LV_OBJ_FLAG_HIDDEN);

        // WEIGHT

        lv_label_set_text(
            weightLabel,
            "NEW");

        lv_obj_set_style_text_color(
            weightLabel,
            textColor,
            0);

        lv_label_set_text(
            weightUnitLabel,
            "");

        lv_obj_set_style_border_color(
            weightCircle,
            textColor,
            0);

        // MATERIAL

        lv_label_set_text(
            materialLabel,
            spool->material.c_str());

        lv_obj_set_style_text_color(
            materialLabel,
            textColor,
            0);

        // BRAND

        lv_label_set_text(
            brandLabel,
            "");

        // CLICKABLE

        lv_obj_clear_flag(
            root,
            LV_OBJ_FLAG_CLICKABLE);

        return;
    }

    lv_obj_clear_flag(
        idLabel,
        LV_OBJ_FLAG_HIDDEN);

    lv_obj_clear_flag(
        weightCircle,
        LV_OBJ_FLAG_HIDDEN);

    lv_obj_add_flag(
        root,
        LV_OBJ_FLAG_CLICKABLE);

    lv_color_t textColor =
        isDarkColor(
            spool->color.c_str())
            ? lv_color_white()
            : lv_color_black();

    lv_obj_set_style_bg_color(
        root,
        hexToColor(
            spool->color.c_str()),
        0);

    // ==========================
    // SLOT
    // ==========================

    lv_label_set_text(
        slotLabel,
        spool->slot.c_str());

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
            1,
            0);

        lv_obj_set_style_border_color(
            slotContainer,
            lv_color_black(),
            0);

        lv_obj_set_style_text_color(
            slotLabel,
            lv_color_black(),
            0);
    }
    else
    {

        lv_obj_set_style_bg_opa(
            slotContainer,
            LV_OPA_TRANSP,
            0);

        lv_obj_set_style_border_width(
            slotContainer,
            0,
            0);

        lv_obj_set_style_text_color(
            slotLabel,
            textColor,
            0);
    }

    // ==========================
    // ID
    // ==========================

    char idText[24];

    sprintf(
        idText,
        "%d",
        spool->id);

    lv_label_set_text(
        idLabel,
        idText);

    // ==========================
    // WEIGHT
    // ==========================

    char weightText[24];

    sprintf(
        weightText,
        "%d",
        spool->weight);

    lv_label_set_text(
        weightLabel,
        weightText);

    lv_obj_set_style_text_color(
        weightLabel,
        textColor,
        0);

    lv_obj_set_style_text_color(
        weightUnitLabel,
        textColor,
        0);

    lv_obj_set_style_border_color(
        weightCircle,
        textColor,
        0);

    // ==========================
    // MATERIAL
    // ==========================

    lv_label_set_text(
        materialLabel,
        spool->material.c_str());

    lv_obj_set_style_text_color(
        materialLabel,
        textColor,
        0);

    // ==========================
    // BRAND
    // ==========================

    lv_label_set_text(
        brandLabel,
        spool->brand.c_str());

    lv_obj_set_style_text_color(
        brandLabel,
        textColor,
        0);
}

void SlotCardV2::onClick(
    lv_event_t *event)
{

    Spool *spool =
        static_cast<Spool *>(
            lv_event_get_user_data(event));

    Navigation::push(new SpoolDetailsScreen(spool));
}
