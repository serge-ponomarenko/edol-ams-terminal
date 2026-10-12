#include "terminal_enrollment_service.h"

#include "../../settings/settings_service.h"
#include "../../settings/terminal_credential_store.h"
#include "../http/http_service.h"
#include "terminal_api.h"
#include "../../../utils/json/json_utils.h"

bool TerminalEnrollmentService::start(const String &pairingCode)
{
    Settings &settings = SettingsService::get();
    String normalizedCode = pairingCode;
    normalizedCode.toUpperCase();
    bool lettersOnly = normalizedCode.length() == 11;
    for (size_t index = 0; lettersOnly && index < normalizedCode.length(); index++)
    {
        lettersOnly = normalizedCode[index] >= 'A' && normalizedCode[index] <= 'Z';
    }
    if (requestId >= 0 || !lettersOnly)
    {
        error = "Enter the 11-letter pairing code";
        return false;
    }
    if (settings.amsHost[0] == '\0' || settings.amsPort <= 0 || settings.amsPort > 65535)
    {
        error = "Enter the AMS address and port";
        return false;
    }
    String url = TerminalApi::url("/api/terminal/v1/enroll");
    String body = "{\"pairingCode\":\"" + normalizedCode + "\"}";
    requestId = HttpService::post(url, body);
    if (requestId < 0)
    {
        error = "Request queue is busy";
        return false;
    }
    error = "";
    return true;
}

void TerminalEnrollmentService::update()
{
    if (requestId < 0 || !HttpService::isCompleted(requestId))
    {
        return;
    }
    if (!HttpService::isSuccess(requestId))
    {
        int responseCode = HttpService::getResponseCode(requestId);
        if (responseCode == 401)
        {
            error = "Pairing code is invalid, expired, or already used";
        }
        else if (responseCode == 429)
        {
            error = "Too many enrollment attempts. Wait before retrying";
        }
        else if (responseCode > 0)
        {
            error = "AMS rejected enrollment. Check the printer and pairing code";
        }
        else
        {
            error = SettingsService::get().amsUseHttps
                    ? "HTTPS failed. Check the AMS address, port, and trusted CA"
                    : "Cannot reach AMS. Check its address, port, WiFi, and firewall";
        }
        HttpService::clear(requestId);
        requestId = -1;
        return;
    }
    String body = HttpService::getResponse(requestId);
    HttpService::clear(requestId);
    requestId = -1;
    String terminalId = extractJsonString(body, "terminalId");
    String secret = extractJsonString(body, "secret");
    if (!TerminalCredentialStore::save(terminalId, secret))
    {
        error = "Terminal credential storage is unavailable";
        return;
    }
    SettingsService::get().secureMode = true;
    SettingsService::save();
    error = "";
}

bool TerminalEnrollmentService::isBusy()
{
    return requestId >= 0;
}

const String &TerminalEnrollmentService::lastError()
{
    return error;
}
