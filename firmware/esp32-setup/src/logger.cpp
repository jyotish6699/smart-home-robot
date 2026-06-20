#include <Arduino.h>

#include "logger.h"
#include "telnet_logger.h"

String logHistory = "";

const int MAX_LOG_SIZE = 5000;

void logInfo(const String &message)
{
    Serial.println(message);

    logHistory += message + "\n";

    if (logHistory.length() > MAX_LOG_SIZE)
    {
        logHistory.remove(
            0,
            logHistory.length() - MAX_LOG_SIZE
        );
    }

    telnetPrintln(message);
}

String getLogHistory()
{
    return logHistory;
}