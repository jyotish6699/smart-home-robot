#include <Arduino.h>

#include <WiFi.h>
#include <WebServer.h>

#include <LittleFS.h>

#include "remote_control.h"
#include "motor_driver.h"
#include "logger.h"

WebServer server(80);

String getContentType(const String &filename)
{
    if (filename.endsWith(".html"))
        return "text/html";

    if (filename.endsWith(".css"))
        return "text/css";

    if (filename.endsWith(".js"))
        return "application/javascript";

    return "text/plain";
}

bool serveFile(String path)
{
    if (path.endsWith("/"))
    {
        path += "index.html";
    }

    if (!LittleFS.exists(path))
    {
        return false;
    }

    File file = LittleFS.open(path, "r");

    server.streamFile(
        file,
        getContentType(path)
    );

    file.close();

    return true;
}

void handleForward()
{
    logInfo("[REMOTE] Forward");

    moveForward();

    server.send(200, "text/plain", "OK");
}

void handleBackward()
{
    logInfo("[REMOTE] Backward");

    moveBackward();

    server.send(200, "text/plain", "OK");
}

void handleLeft()
{
    logInfo("[REMOTE] Left");

    turnLeft();

    server.send(200, "text/plain", "OK");
}

void handleRight()
{
    logInfo("[REMOTE] Right");

    turnRight();

    server.send(200, "text/plain", "OK");
}

void handleStop()
{
    logInfo("[REMOTE] Stop");

    stopMotors();

    server.send(200, "text/plain", "OK");
}

void handleNotFound()
{
    if (serveFile(server.uri()))
    {
        return;
    }

    server.send(
        404,
        "text/plain",
        "404 Not Found"
    );
}

void setupRemoteControl()
{
    if (!LittleFS.begin())
    {
        logInfo("[REMOTE] LittleFS Mount Failed");

        return;
    }

    logInfo("[REMOTE] LittleFS Ready");

    server.on(
        "/",
        HTTP_GET,
        []()
        {
            serveFile("/index.html");
        }
    );

    server.on("/forward", HTTP_GET, handleForward);

    server.on("/backward", HTTP_GET, handleBackward);

    server.on("/left", HTTP_GET, handleLeft);

    server.on("/right", HTTP_GET, handleRight);

    server.on("/stop", HTTP_GET, handleStop);

    server.onNotFound(handleNotFound);

    server.begin();

    logInfo("[REMOTE] HTTP Server Started");
}

void handleRemoteControl()
{
    server.handleClient();
}