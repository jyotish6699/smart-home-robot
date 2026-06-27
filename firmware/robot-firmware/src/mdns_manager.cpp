#include <ESPmDNS.h>

#include "mdns_manager.h"
#include "logger.h"

bool setupMDNS()
{
    logInfo("[MDNS] Starting...");

    if (!MDNS.begin("aegis"))
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
        "[MDNS] Hostname: aegis.local"
    );

    logInfo(
        "[MDNS] HTTP Service Registered"
    );

    return true;
}