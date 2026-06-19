#include <ArduinoOTA.h>
#include "ota_manager.h"

void setupOTA()
{
    ArduinoOTA.setHostname("smart-home-robot");

    ArduinoOTA.onStart([]()
    {
        Serial.println("OTA Start");
    });

    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total)
    {
        Serial.printf(
            "Progress: %u%%\r",
            (progress * 100) / total
        );
    });

    ArduinoOTA.onEnd([]()
    {
        Serial.println("OTA End");
    });

    ArduinoOTA.onError([](ota_error_t error)
    {
        Serial.printf("OTA Error[%u]\n", error);
    });

    ArduinoOTA.begin();

    Serial.println("OTA Ready");
}