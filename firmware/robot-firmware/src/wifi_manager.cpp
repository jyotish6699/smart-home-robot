#include <WiFi.h>

#include "wifi_manager.h"
#include "secrets.h"
#include "logger.h"

void connectWiFi()
{
    logInfo("[WIFI] connectWiFi() called");

    WiFi.mode(WIFI_STA);

    // IPAddress local_IP(10,249,232,50);
    // IPAddress gateway(10,249,232,186);
    // IPAddress subnet(255,255,255,0);

    // WiFi.config(local_IP, gateway, subnet);

    logInfo("[WIFI] Connecting to SSID: " + String(WIFI_SSID));

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);

        logInfo(
            "[WIFI] Status = " +
            String(WiFi.status())
        );
    }

    logInfo("[WIFI] Connected");
    logInfo("[WIFI] SSID: " + String(WIFI_SSID));
    logInfo("[WIFI] IP: " + WiFi.localIP().toString());
    logInfo("[WIFI] Gateway: " + WiFi.gatewayIP().toString());
    logInfo("[WIFI] Subnet: " + WiFi.subnetMask().toString());
}