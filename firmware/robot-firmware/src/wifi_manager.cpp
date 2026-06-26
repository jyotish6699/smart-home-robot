#include <WiFi.h>

#include "wifi_manager.h"
#include "wifi_credentials.h"
#include "logger.h"

bool connectWiFi()
{
    logInfo("[WIFI] connectWiFi() called");

    WiFi.mode(WIFI_STA);

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

        unsigned long startTime = millis();

        while (WiFi.status() != WL_CONNECTED &&
               millis() - startTime < 10000)
        {
            delay(500);

            logInfo(
                "[WIFI] Status = " +
                String(WiFi.status())
            );
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

            logInfo(
                "[WIFI] Gateway: " +
                WiFi.gatewayIP().toString()
            );

            logInfo(
                "[WIFI] Subnet: " +
                WiFi.subnetMask().toString()
            );

            return true;
        }

        logInfo(
            "[WIFI] Failed: " +
            String(KNOWN_WIFI_NETWORKS[i].ssid)
        );

        WiFi.disconnect(true);

        delay(500);
    }

    logInfo("[WIFI] No Known Network Available");

    return false;
}