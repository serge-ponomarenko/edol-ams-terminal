#include "nfc_service.h"

#include "../../../hardware/nfc/nfc.h"
#include "../../../hardware/display/display.h"

void NfcService::startWrite(
    uint32_t spoolId)
{
    pendingSpoolId = spoolId;
    state = NfcWriteState::WAITING_FOR_TAG;
    stateChangedAt = millis();
}

void NfcService::cancel()
{
    state = NfcWriteState::IDLE;
}

bool NfcService::isBusy()
{
    return state != NfcWriteState::IDLE;
}

NfcWriteState NfcService::getState()
{
    return state;
}

bool NfcService::hasPendingScan()
{
    return pendingScan;
}

uint32_t NfcService::consumePendingScan()
{
    pendingScan = false;

    return pendingScanSpoolId;
}

void NfcService::update()
{
    if (state == NfcWriteState::WAITING_FOR_TAG)
    {
        bool present = nfcIsTagPresent();

        if (!present)
        {
            return;
        }

        bool success = nfcWriteEdolTag(pendingSpoolId);
        state =
            success
                ? NfcWriteState::SUCCESS
                : NfcWriteState::ERROR;
        stateChangedAt = millis();
    }
    else if (
        state == NfcWriteState::SUCCESS ||
        state == NfcWriteState::ERROR)
    {
        if (millis() - stateChangedAt > 1500)
        {
            state = NfcWriteState::IDLE;
        }
    }

    // ==========================
    // BACKGROUND NFC SCAN
    // ==========================

    if (isBusy())
    {
        return;
    }

    EdolNfcData data;

    auto result = nfcReadEdolTag(data);

    if (result == NfcReadResult::NO_TAG)
    {
        missingPolls++;
        if (missingPolls >= 3)
        {
            tagPresent = false;
        }
        return;
    }

    if (result != NfcReadResult::OK)
    {
        return;
    }

    missingPolls = 0;

    if (tagPresent)
    {
        return;
    }

    tagPresent = true;

    displayTouch();

    pendingScanSpoolId = data.spoolId;

    pendingScan = true;
}