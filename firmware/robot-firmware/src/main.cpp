#include <Arduino.h>
#include <ArduinoOTA.h>

#include "wifi_manager.h"
#include "ota_manager.h"
#include "logger.h"
#include "telnet_logger.h"
#include "motor_driver.h"
#include "remote_control.h"
#include "mdns_manager.h"
#include "motion_engine.h"

unsigned long lastLog = 0;

void setup()
{
    Serial.begin(115200);

    if (!connectWiFi())
    {
        logInfo("[SYSTEM] WiFi Connection Failed");

        while (true)
        {
            delay(1000);
        }
    }

    initTelnetLogger();

    setupOTA();

    if (!setupMDNS())
    {
        logInfo("[SYSTEM] mDNS Startup Failed");
    }

    setupMotors();

    setupMotionEngine();

    setupRemoteControl();

    logInfo("[SYSTEM] Boot Complete");
}

void loop()
{
    handleTelnetLogger();

    ArduinoOTA.handle();

    handleRemoteControl();

    if (millis() - lastLog > 5000)
    {
        logInfo(
            "[SYSTEM] Uptime: " +
            String(millis() / 1000) +
            " sec"
        );

        lastLog = millis();
    }
}