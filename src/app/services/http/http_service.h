#pragma once

#include "http_request.h"

class HttpService
{

public:
    static void update();

    static int get(const String &url);

    static bool isCompleted(int requestId);

    static bool isSuccess(int requestId);

    static const String& getResponse(int requestId);

    static int getResponseCode(int requestId);

    static void clear(int requestId);

private:
    static constexpr int MAX_REQUESTS = 2;

    static HttpRequest requests[MAX_REQUESTS];
};