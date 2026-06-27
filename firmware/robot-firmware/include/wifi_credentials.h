#ifndef WIFI_CREDENTIALS_H
#define WIFI_CREDENTIALS_H

struct WiFiCredential
{
    const char *ssid;
    const char *password;
};

static const WiFiCredential KNOWN_WIFI_NETWORKS[] =
{
    {
        "TECNO",
        "11111111"
    },

    {
        "Redmi 13 5G",
        "11111111"
    }
};

static const int KNOWN_WIFI_NETWORK_COUNT =
sizeof(KNOWN_WIFI_NETWORKS) /
sizeof(KNOWN_WIFI_NETWORKS[0]);

#endif