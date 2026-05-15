#include "ui.h"

#include <lvgl.h>

#include "../hardware/touch/touch.h"

#include <TFT_eSPI.h>

extern TFT_eSPI tft;

// ==========================
// LVGL DRAW BUFFER
// ==========================

static lv_disp_draw_buf_t drawBuf;

static lv_color_t buf1[320 * 10];
static lv_color_t buf2[320 * 10];

// ==========================
// DISPLAY FLUSH
// ==========================

static void displayFlush(
    lv_disp_drv_t *disp,
    const lv_area_t *area,
    lv_color_t *color_p)
{

    uint32_t width =
        area->x2 - area->x1 + 1;

    uint32_t height =
        area->y2 - area->y1 + 1;

    tft.startWrite();

    tft.setAddrWindow(
        area->x1,
        area->y1,
        width,
        height);

    tft.pushColors(
        (uint16_t *)&color_p->full,
        width * height,
        true);

    tft.endWrite();

    lv_disp_flush_ready(disp);
}

// ==========================
// TOUCH INPUT
// ==========================

static void touchRead(
    lv_indev_drv_t *indev,
    lv_indev_data_t *data)
{

    data->point.x = touchGetX();
    data->point.y = touchGetY();

    data->state =
        touchIsPressed()
            ? LV_INDEV_STATE_PR
            : LV_INDEV_STATE_REL;
}

// ==========================
// UI SETUP
// ==========================

void uiSetup()
{

    lv_init();

    // ==========================
    // DRAW BUFFER
    // ==========================

    lv_disp_draw_buf_init(
        &drawBuf,
        buf1,
        buf2,
        320 * 10);

    // ==========================
    // DISPLAY DRIVER
    // ==========================

    static lv_disp_drv_t displayDriver;

    lv_disp_drv_init(
        &displayDriver);

    displayDriver.hor_res = 320;
    displayDriver.ver_res = 240;

    displayDriver.flush_cb =
        displayFlush;

    displayDriver.draw_buf =
        &drawBuf;

    lv_disp_drv_register(
        &displayDriver);

    // ==========================
    // TOUCH DRIVER
    // ==========================

    static lv_indev_drv_t inputDriver;

    lv_indev_drv_init(
        &inputDriver);

    inputDriver.type =
        LV_INDEV_TYPE_POINTER;

    inputDriver.read_cb =
        touchRead;

    lv_indev_drv_register(
        &inputDriver);
}

// ==========================
// UI LOOP
// ==========================

void uiLoop()
{
    static uint32_t lastTick = millis();
    uint32_t now = millis();
    lv_tick_inc(now - lastTick);
    lastTick = now;
    lv_timer_handler();
    delay(5);
}