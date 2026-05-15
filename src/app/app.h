#pragma once

#include <memory>

class LoadingScreen;

class App
{
public:
    void setup();

    void update();

    static LoadingScreen *loadingScreen;

private:
    bool appReady = false;

};