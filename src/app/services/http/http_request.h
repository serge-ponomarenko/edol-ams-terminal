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

    enum class Method
    {
        GET,
        POST
    } method = Method::GET;

    String body;

    String authorization;

    String response;

    int responseCode = 0;
};
