#pragma once

#include <Arduino.h>

enum class HttpRequestState
{
    EMPTY,
    QUEUED,
    LOADING,
    SUCCESS,
    ERROR
};

struct HttpRequest
{
    HttpRequestState state = HttpRequestState::EMPTY;

    String url;

    String response;

    int responseCode = 0;
};