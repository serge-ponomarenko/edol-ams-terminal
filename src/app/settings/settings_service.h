#pragma once

#include "settings.h"

class SettingsService {

public:

    static void begin();

    static Settings& get();

    static bool load();

    static bool save();

private:

    static Settings settings;
};