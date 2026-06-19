#include <Arduino.h>
#include <ArduinoOTA.h>

#include "wifi_manager.h"
#include "ota_manager.h"
#include "esp_system.h"

void setup()
{
    Serial.begin(115200);
    Serial.println("BOOT");

    Serial.println();
    Serial.println("========================");
    Serial.println("SMART HOME ROBOT");
    Serial.println("Version: v0.0.4 OTA TEST");
    Serial.println("OTA Upload Successful");
    Serial.println("========================");

    connectWiFi();

    setupOTA();
}

void loop()
{
    ArduinoOTA.handle();

    delay(10);
}