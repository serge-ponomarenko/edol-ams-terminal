#pragma once

class Screen {
public:
    virtual ~Screen() = default;

    virtual void create() = 0;
    virtual void destroy() = 0;
};