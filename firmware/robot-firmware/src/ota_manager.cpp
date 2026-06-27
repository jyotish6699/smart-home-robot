#include <ArduinoOTA.h>

#include "ota_manager.h"
#include "logger.h"

void setupOTA()
{
    ArduinoOTA.setHostname("aegis");

    ArduinoOTA.onStart([]()
    {
        logInfo("[OTA] Start");
    });

    ArduinoOTA.onProgress([](unsigned int progress,
                             unsigned int total)
    {
        static int lastPercent = -1;

        int percent = (progress * 100) / total;

        if (percent != lastPercent)
        {
            lastPercent = percent;

            logInfo(
                "[OTA] Progress: " +
                String(percent) +
                "%"
            );
        }
    });

    ArduinoOTA.onEnd([]()
    {
        logInfo("[OTA] End");
    });

    ArduinoOTA.onError([](ota_error_t error)
    {
        logInfo(
            "[OTA] Error: " +
            String(error)
        );
    });

    ArduinoOTA.begin();

    logInfo("[OTA] Ready");
}