#include "terminal_enrollment_service.h"

#include "../../settings/settings_service.h"
#include "../../settings/terminal_credential_store.h"
#include "../http/http_service.h"
#include "../../../utils/json/json_utils.h"

bool TerminalEnrollmentService::start(const String &pairingCode)
{
    if (requestId >= 0 || pairingCode.length() != 10 || !TerminalCredentialStore::isHardwareProtected())
    {
        error = "Enrollment prerequisites are unavailable";
        return false;
    }
    Settings &settings = SettingsService::get();
    String url = "https://" + String(settings.amsHost) + ":" + settings.amsPort + "/api/terminal/v1/enroll";
    String body = "{\"printerId\":\"" + String(settings.printerId)
            + "\",\"pairingCode\":\"" + pairingCode + "\"}";
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
        error = "Enrollment rejected or TLS validation failed";
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
        error = "Secure credential storage is unavailable";
        return;
    }
    SettingsService::get().secureMode = true;
    SettingsService::save();
}

bool TerminalEnrollmentService::isBusy()
{
    return requestId >= 0;
}

const String &TerminalEnrollmentService::lastError()
{
    return error;
}
