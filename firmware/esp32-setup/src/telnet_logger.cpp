#include <WiFi.h>
#include "telnet_logger.h"
#include "logger.h"

WiFiServer telnetServer(23);
WiFiClient telnetClient;

void initTelnetLogger()
{
    telnetServer.begin();
    telnetServer.setNoDelay(true);

    Serial.println("[TELNET] Server Started");
}

void handleTelnetLogger()
{
    if (telnetServer.hasClient())
    {
        if (telnetClient && telnetClient.connected())
        {
            telnetClient.stop();
        }

        telnetClient = telnetServer.available();

        if (telnetClient)
        {
            telnetClient.println();
            telnetClient.println("========================");
            telnetClient.println("SMART HOME ROBOT");
            telnetClient.println("========================");

            telnetClient.println();
            telnetClient.println("Telnet Connected");
            telnetClient.println();

            telnetClient.println("----- LOG HISTORY -----");
            telnetClient.println();

            telnetClient.print(getLogHistory());

            telnetClient.println();
            telnetClient.println("----- LIVE LOGS -----");
            telnetClient.println();

            Serial.println("[TELNET] Client Connected");
        }
    }
}

void telnetPrintln(const String &message)
{
    if (telnetClient && telnetClient.connected())
    {
        telnetClient.println(message);
    }
}