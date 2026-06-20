#include <Arduino.h>
#include <ArduinoOTA.h>

#include "wifi_manager.h"
#include "ota_manager.h"
#include "esp_system.h"
#include "logger.h"
#include "telnet_logger.h"

unsigned long lastLog = 0;

void setup()
{
    Serial.begin(115200);

    logInfo("[SYSTEM] Booting");

    connectWiFi();

    initTelnetLogger();

    setupOTA();

    logInfo("[SYSTEM] Boot Complete");
}

void loop()
{
    handleTelnetLogger();

    ArduinoOTA.handle();

    if (millis() - lastLog > 5000)
    {
        logInfo(
            "[SYSTEM] Uptime: " +
            String(millis() / 1000) +
            " sec"
        );

        lastLog = millis();
    }

    delay(10);
}