#include <WiFi.h>

#include "wifi_manager.h"
#include "wifi_credentials.h"
#include "logger.h"

static unsigned long lastRetry = 0;

bool connectWiFi()
{
    logInfo("[WIFI] Starting");

    WiFi.mode(WIFI_STA);

    WiFi.setSleep(false);

    WiFi.disconnect(true);

    delay(500);

    for (int i = 0; i < KNOWN_WIFI_NETWORK_COUNT; i++)
    {
        logInfo(
            "[WIFI] Trying: " +
            String(KNOWN_WIFI_NETWORKS[i].ssid)
        );

        WiFi.begin(
            KNOWN_WIFI_NETWORKS[i].ssid,
            KNOWN_WIFI_NETWORKS[i].password
        );

        unsigned long start = millis();

        while (
            WiFi.status() != WL_CONNECTED &&
            millis() - start < 10000
        )
        {
            delay(250);
        }

        if (WiFi.status() == WL_CONNECTED)
        {
            logInfo("[WIFI] Connected");

            logInfo(
                "[WIFI] SSID: " +
                WiFi.SSID()
            );

            logInfo(
                "[WIFI] IP: " +
                WiFi.localIP().toString()
            );

            return true;
        }

        WiFi.disconnect(true);

        delay(500);
    }

    logInfo("[WIFI] No Known Network");

    return false;
}

bool isWiFiConnected()
{
    return WiFi.status() == WL_CONNECTED;
}

void handleWiFi()
{
    if (WiFi.status() == WL_CONNECTED)
    {
        return;
    }

    if (millis() - lastRetry < 5000)
    {
        return;
    }

    lastRetry = millis();

    logInfo("[WIFI] Reconnecting...");

    WiFi.reconnect();
}