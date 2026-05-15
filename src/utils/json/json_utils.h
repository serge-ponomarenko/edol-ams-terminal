#pragma once

#include <Arduino.h>

String extractJsonString(
    const String &json,
    const String &key);

int extractJsonInt(
    const String &json,
    const String &key);

float extractJsonFloat(
    const String &json,
    const String &key);

bool extractJsonBool(
    const String &json,
    const String &key);

String extractJsonObject(
    const String &json,
    const String &key);

String extractJsonArrayObject(
    const String &json,
    const String &key,
    int index);