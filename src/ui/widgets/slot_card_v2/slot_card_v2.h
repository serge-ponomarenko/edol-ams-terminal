#pragma once

#include <lvgl.h>

#include "../../../models/spool/spool.h"

class SlotCardV2
{
public:
    void create(
        lv_obj_t *parent,
        Spool *spool);

    lv_obj_t *getRoot();

    void setSpool(
        Spool *spool);

private:
    static void onClick(
        lv_event_t *event);

    lv_obj_t *root = nullptr;

    Spool *spool = nullptr;

    lv_obj_t *slotLabel = nullptr;

    lv_obj_t *idLabel = nullptr;

    lv_obj_t *weightLabel = nullptr;

    lv_obj_t *weightUnitLabel = nullptr;

    lv_obj_t *materialLabel = nullptr;

    lv_obj_t *brandLabel = nullptr;

    lv_obj_t *slotContainer = nullptr;

    lv_obj_t *weightCircle = nullptr;
    
};