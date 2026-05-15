#include "navigation.h"

Screen *Navigation::screenStack[Navigation::MAX_STACK];

int Navigation::stackSize = 0;

void Navigation::push(
    Screen *screen)
{
    if (stackSize > 0)
    {
        screenStack[stackSize - 1]
            ->destroy();
    }

    if (stackSize >= MAX_STACK)
    {
        delete screen;
        return;
    }

    screenStack[stackSize++] = screen;

    screen->create();
}

void Navigation::back()
{
    if (stackSize <= 1)
    {
        return;
    }

    screenStack[stackSize - 1]
        ->destroy();

    delete screenStack[stackSize - 1];

    stackSize--;

    screenStack[stackSize - 1]
        ->create();
}

void Navigation::replace(
    Screen *screen)
{
    if (stackSize > 0)
    {
        screenStack[stackSize - 1]
            ->destroy();

        delete screenStack[stackSize - 1];

        stackSize--;
    }

    screenStack[stackSize++] = screen;

    screen->create();
}