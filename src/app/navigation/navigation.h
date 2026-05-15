#pragma once

#include "../screens/screen.h"

class Navigation
{
public:
    static void push(Screen *screen);

    static void back();

    static void replace(Screen *screen);

private:
    static constexpr int MAX_STACK = 8;

    static Screen *screenStack[MAX_STACK];

    static int stackSize;
};