#include <Arduino.h>
#include <ArduinoOTA.h>

#include "wifi_manager.h"
#include "ota_manager.h"
#include "logger.h"
#include "telnet_logger.h"
#include "motor_driver.h"
#include "remote-control.h"

unsigned long lastLog = 0;
unsigned long motorTimer = 0;
int motorState = 0;

void setup()
{
    Serial.begin(115200);

    connectWiFi();

    initTelnetLogger();

    setupOTA();

    setupMotors();

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

    if (millis() - motorTimer > 4000)
    {
        motorTimer = millis();

        switch (motorState)
        {
            case 0:
                logInfo("[TEST] Forward");
                moveForward();
                break;

            case 1:
                logInfo("[TEST] Backward");
                moveBackward();
                break;

            case 2:
                logInfo("[TEST] Left");
                turnLeft();
                break;

            case 3:
                logInfo("[TEST] Right");
                turnRight();
                break;

            case 4:
                logInfo("[TEST] Stop");
                stopMotors();
                break;
        }

        motorState++;

        if (motorState > 4)
        {
            motorState = 0;
        }
    }
}