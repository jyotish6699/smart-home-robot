#include <ESPmDNS.h>

#include "mdns_manager.h"
#include "logger.h"

bool setupMDNS()
{
    logInfo("[MDNS] Starting...");

    if (!MDNS.begin("smart-home-robot"))
    {
        logInfo("[MDNS] Failed");

        return false;
    }

    MDNS.addService(
        "http",
        "tcp",
        80
    );

    logInfo(
        "[MDNS] Hostname: smart-home-robot.local"
    );

    logInfo(
        "[MDNS] HTTP Service Registered"
    );

    return true;
}