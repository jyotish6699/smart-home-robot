#include <Arduino.h>
#include <ArduinoOTA.h>
#include <WiFi.h>

#include "wifi_manager.h"
#include "ota_manager.h"
#include "logger.h"
#include "telnet_logger.h"
#include "motor_driver.h"
#include "remote_control.h"
#include "mdns_manager.h"
#include "motion_engine.h"
#include "motion_profile.h"

unsigned long lastLog = 0;

void setup()
{
    Serial.begin(115200);

    connectWiFi();

    initTelnetLogger();

    setupOTA();

    setupMDNS();

    setupMotors();

    setupMotionProfile();

    setupMotionEngine();

    setupRemoteControl();

    logInfo("[SYSTEM] Boot Complete");
}

void loop()
{
    handleWiFi();

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