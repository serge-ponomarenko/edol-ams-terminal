#include "json_utils.h"

String extractJsonString(
    const String &json,
    const String &key)
{
    char nullPattern[64];

    snprintf(
        nullPattern,
        sizeof(nullPattern),
        "\"%s\":null",
        key.c_str());

    if (strstr(
            json.c_str(),
            nullPattern) != nullptr)
    {
        return "";
    }

    char pattern[64];

    snprintf(
        pattern,
        sizeof(pattern),
        "\"%s\":\"",
        key.c_str());

    const char *start =
        strstr(
            json.c_str(),
            pattern);

    if (!start)
    {
        return "";
    }

    start += strlen(pattern);

    const char *end =
        strchr(start, '"');

    if (!end)
    {
        return "";
    }

    String result;

    result.reserve(end - start);

    result.concat(
        start,
        end - start);

    return result;
}

int extractJsonInt(
    const String &json,
    const String &key)
{
    char pattern[64];

    snprintf(
        pattern,
        sizeof(pattern),
        "\"%s\":",
        key.c_str());

    const char *start =
        strstr(json.c_str(), pattern);

    if (!start)
    {
        return 0;
    }

    start += strlen(pattern);

    return atoi(start);
}

float extractJsonFloat(
    const String &json,
    const String &key)
{
    char pattern[64];

    snprintf(
        pattern,
        sizeof(pattern),
        "\"%s\":",
        key.c_str());

    const char *start =
        strstr(json.c_str(), pattern);

    if (!start)
    {
        return 0;
    }

    start += strlen(pattern);

    return atof(start);
}

bool extractJsonBool(
    const String &json,
    const String &key)
{
    char pattern[64];

    snprintf(
        pattern,
        sizeof(pattern),
        "\"%s\":true",
        key.c_str());

    return strstr(
               json.c_str(),
               pattern) != nullptr;
}

String extractJsonObject(
    const String &json,
    const String &key)
{
    String nullPattern =
        "\"" + key + "\":null";

    if (json.indexOf(nullPattern) >= 0)
    {
        return "";
    }

    String pattern =
        "\"" + key + "\":{";

    int start =
        json.indexOf(pattern);

    if (start < 0)
    {
        return "";
    }

    start =
        json.indexOf("{", start);

    if (start < 0)
    {
        return "";
    }

    int depth = 0;

    for (int i = start; i < json.length(); i++)
    {
        if (json[i] == '{')
        {
            depth++;
        }
        else if (json[i] == '}')
        {
            depth--;

            if (depth == 0)
            {
                return json.substring(
                    start,
                    i + 1);
            }
        }
    }

    return "";
}

String extractJsonArrayObject(
    const String &json,
    const String &key,
    int index)
{
    String pattern =
        "\"" + key + "\":[";

    int start =
        json.indexOf(pattern);

    if (start < 0)
    {
        return "";
    }

    start =
        json.indexOf("[", start);

    if (start < 0)
    {
        return "";
    }

    int depth = 0;

    int objectIndex = -1;

    int objectStart = -1;

    for (int i = start; i < json.length(); i++)
    {
        if (json[i] == '{')
        {
            if (depth == 0)
            {
                objectIndex++;

                if (objectIndex == index)
                {
                    objectStart = i;
                }
            }

            depth++;
        }
        else if (json[i] == '}')
        {
            depth--;

            if (
                depth == 0 &&
                objectIndex == index &&
                objectStart >= 0)
            {
                return json.substring(
                    objectStart,
                    i + 1);
            }
        }
    }

    return "";
}