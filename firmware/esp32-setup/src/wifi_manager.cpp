#include <WiFi.h>
#include "wifi_manager.h"
#include "secrets.h"

void connectWiFi()
{
    Serial.println("connectWiFi() called");
    Serial.print("Connecting to: ");
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    Serial.print("Connecting");

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);

        Serial.print(".");
        Serial.print(" Status=");
        Serial.println(WiFi.status());
    }

    Serial.println();
    Serial.println("WiFi Connected");

    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
}