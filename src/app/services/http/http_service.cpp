#include "http_service.h"

#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include <time.h>

#ifndef EDOL_AMS_ROOT_CA_PEM
#define EDOL_AMS_ROOT_CA_PEM ""
#endif
#include <WiFiClientSecure.h>

#include "../wifi/wifi_service.h"

HttpRequest
    HttpService::requests[MAX_REQUESTS];

namespace {
bool tlsClockReady()
{
    if (time(nullptr) > 1704067200)
    {
        return true;
    }
    configTime(0, 0, "pool.ntp.org", "time.nist.gov");
    for (int attempt = 0; attempt < 20; attempt++)
    {
        if (time(nullptr) > 1704067200)
        {
            return true;
        }
        delay(100);
    }
    return false;
}
}

int HttpService::get(const String &url)
{
    return get(url, "");
}

int HttpService::get(const String &url, const String &authorization)
{
    for (int i = 0; i < MAX_REQUESTS; i++)
    {
        if (requests[i].state == HttpRequestState::EMPTY)
        {
            requests[i].url = url;
            requests[i].method = HttpRequest::Method::GET;
            requests[i].authorization = authorization;
            requests[i].body.clear();
            requests[i].response.clear();
            requests[i].responseCode = 0;
            requests[i].state = HttpRequestState::QUEUED;
            return i;
        }
    }
    return -1;
}

int HttpService::post(const String &url, const String &body, const String &authorization)
{
    for (int i = 0; i < MAX_REQUESTS; i++)
    {
        if (requests[i].state == HttpRequestState::EMPTY)
        {
            requests[i].url = url;
            requests[i].method = HttpRequest::Method::POST;
            requests[i].authorization = authorization;
            requests[i].body = body;
            requests[i].response.clear();
            requests[i].responseCode = 0;
            requests[i].state = HttpRequestState::QUEUED;
            return i;
        }
    }
    return -1;
}

bool HttpService::isCompleted(int requestId)
{
    auto state = requests[requestId].state;
    return
        state == HttpRequestState::SUCCESS ||
        state == HttpRequestState::ERROR;
}

bool HttpService::isSuccess(int requestId)
{
    return requests[requestId].state == HttpRequestState::SUCCESS;
}

const String& HttpService::getResponse(int requestId)
{
    return requests[requestId].response;
}

int HttpService::getResponseCode(int requestId)
{
    return requests[requestId].responseCode;
}

void HttpService::clear(int requestId)
{
    requests[requestId] = HttpRequest();
}

void HttpService::update()
{
    if (!WifiService::isConnected())
    {
        return;
    }

    for (int i = 0; i < MAX_REQUESTS; i++)
    {
        auto &request = requests[i];

        if ( request.state != HttpRequestState::QUEUED)
        {
            continue;
        }

        request.state = HttpRequestState::LOADING;

        HTTPClient http;
        WiFiClientSecure secureClient;
        bool secure = request.url.startsWith("https://");
        if (secure)
        {
            if (String(EDOL_AMS_ROOT_CA_PEM).isEmpty() || !tlsClockReady())
            {
                request.responseCode = -1;
                request.state = HttpRequestState::ERROR;
                break;
            }
            secureClient.setCACert(EDOL_AMS_ROOT_CA_PEM);
            if (!http.begin(secureClient, request.url))
            {
                request.responseCode = -1;
                request.state = HttpRequestState::ERROR;
                break;
            }
        }
        else
        {
            http.begin(request.url);
        }
        if (!request.authorization.isEmpty())
        {
            http.addHeader("Authorization", request.authorization);
        }
        int responseCode;
        if (request.method == HttpRequest::Method::POST)
        {
            http.addHeader("Content-Type", "application/json");
            responseCode = http.POST(request.body);
        }
        else
        {
            responseCode = http.GET();
        }

        request.responseCode = responseCode;

        if (responseCode >= 200 && responseCode < 300)
        {
            request.response = http.getString();
            request.state = HttpRequestState::SUCCESS;
        }
        else
        {
            request.state = HttpRequestState::ERROR;
        }

        http.end();

        break;
    }
}
