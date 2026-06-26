#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>

#include "remote-control.h"
#include "logger.h"

WebServer server(80);

void handleRoot()
{
    server.send(
        200,
        "text/html",
        "<h1>Smart Home Robot</h1><p>Remote Control Server Running</p>"
    );
}

void setupRemoteControl()
{
    server.on("/", handleRoot);

    server.begin();

    logInfo("[REMOTE] HTTP Server Started");
}

void handleRemoteControl()
{
    server.handleClient();
}