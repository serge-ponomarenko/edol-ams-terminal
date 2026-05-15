#pragma once

#include <lvgl.h>

#include "../screen.h"

class LoadingScreen : public Screen
{
public:
    void create() override;

    void destroy() override;

    void setStatus(
        const char *text);

    static void onSettingsClick(
        lv_event_t *event);

    lv_obj_t *root = nullptr;

private:
    lv_obj_t *statusLabel = nullptr;
};