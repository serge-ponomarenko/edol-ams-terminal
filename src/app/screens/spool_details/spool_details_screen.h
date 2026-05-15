#pragma once

#include <lvgl.h>

#include "../screen.h"

#include "../../../models/spool/spool.h"

class SpoolDetailsScreen : public Screen
{

public:
    SpoolDetailsScreen(Spool *spool);

    void create() override;
    void destroy() override;

    static void onBackClick(lv_event_t *event);

    static void onEncodeClick(lv_event_t *event);

    static void onEraseClick(lv_event_t *event);

    static void onCancelNfcClick(lv_event_t *event);

    static void onUpdateTimer(lv_timer_t *timer);

private:
    lv_obj_t *root = nullptr;

    lv_obj_t *backButton = nullptr;

    lv_obj_t *nfcModal = nullptr;
    lv_obj_t *nfcModalText = nullptr;
    lv_obj_t *nfcCancelButton = nullptr;
    lv_timer_t *updateTimer = nullptr;

    Spool *spool = nullptr;
};