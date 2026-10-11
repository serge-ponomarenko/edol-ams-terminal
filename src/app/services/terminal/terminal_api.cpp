#include "terminal_api.h"

#include "../../settings/settings_service.h"
#include "../../settings/terminal_credential_store.h"

bool TerminalApi::isReady()
{
    return SettingsService::get().secureMode && TerminalCredentialStore::hasCredential();
}

String TerminalApi::authorization()
{
    String terminalId;
    String secret;
    if (!TerminalCredentialStore::load(terminalId, secret))
    {
        return "";
    }
    return "EDOL-Terminal " + terminalId + "." + secret;
}

String TerminalApi::url(const char *path)
{
    Settings &settings = SettingsService::get();
    return String(settings.amsUseHttps ? "https://" : "http://")
            + String(settings.amsHost) + ":" + settings.amsPort + path;
}

void TerminalApi::factoryReset()
{
    TerminalCredentialStore::clear();
    SettingsService::get().secureMode = false;
    SettingsService::save();
}
