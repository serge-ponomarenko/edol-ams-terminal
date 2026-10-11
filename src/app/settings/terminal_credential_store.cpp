#include "terminal_credential_store.h"

#include <Preferences.h>

namespace {
constexpr const char *NAMESPACE = "edol-terminal";
constexpr const char *TERMINAL_ID_KEY = "terminal-id";
constexpr const char *SECRET_KEY = "secret";
}

bool TerminalCredentialStore::hasCredential()
{
    String terminalId;
    String secret;
    return load(terminalId, secret);
}

bool TerminalCredentialStore::save(const String &terminalId, const String &secret)
{
    if (terminalId.isEmpty() || secret.isEmpty())
    {
        return false;
    }
    Preferences preferences;
    if (!preferences.begin(NAMESPACE, false))
    {
        return false;
    }
    bool saved = preferences.putString(TERMINAL_ID_KEY, terminalId) > 0
            && preferences.putString(SECRET_KEY, secret) > 0;
    preferences.end();
    return saved;
}

bool TerminalCredentialStore::load(String &terminalId, String &secret)
{
    Preferences preferences;
    if (!preferences.begin(NAMESPACE, true))
    {
        return false;
    }
    terminalId = preferences.getString(TERMINAL_ID_KEY, "");
    secret = preferences.getString(SECRET_KEY, "");
    preferences.end();
    return !terminalId.isEmpty() && !secret.isEmpty();
}

void TerminalCredentialStore::clear()
{
    Preferences preferences;
    if (preferences.begin(NAMESPACE, false))
    {
        preferences.clear();
        preferences.end();
    }
}
