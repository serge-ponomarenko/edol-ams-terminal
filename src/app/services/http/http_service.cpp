#include "http_service.h"

#include <HTTPClient.h>

#include "../wifi/wifi_service.h"

HttpRequest
    HttpService::requests[MAX_REQUESTS];

int HttpService::get(const String &url)
{
    for (int i = 0; i < MAX_REQUESTS; i++)
    {
        if (requests[i].state == HttpRequestState::EMPTY)
        {
            requests[i].url = url;
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

        http.begin(request.url);

        int responseCode = http.GET();

        request.responseCode = responseCode;

        if (responseCode == 200)
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