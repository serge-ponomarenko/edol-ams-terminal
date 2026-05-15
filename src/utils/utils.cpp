#include "utils.h"

#include <memory>

lv_color_t hexToColor(
    const char *hex)
{
    unsigned int r, g, b;

    sscanf(
        hex + 1,
        "%02x%02x%02x",
        &r,
        &g,
        &b);

    return lv_color_make(r, g, b);
}

bool isDarkColor(
    const char *hex)
{
    unsigned int r, g, b;

    sscanf(
        hex + 1,
        "%02x%02x%02x",
        &r,
        &g,
        &b);

    int brightness =
        (r * 299 +
         g * 587 +
         b * 114) /
        1000;

    return brightness < 128;
}