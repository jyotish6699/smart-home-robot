#include <Arduino.h>

#include <WiFi.h>
#include <WebServer.h>

#include <LittleFS.h>

#include "remote_control.h"
#include "motor_driver.h"
#include "logger.h"
#include "motion_engine.h"
#include "motion_profile.h"

WebServer server(80);

static unsigned long lastCommandTime = 0;

constexpr unsigned long COMMAND_TIMEOUT = 500;

static bool timeoutTriggered = false;

void handleForward();
void handleBackward();
void handleLeft();
void handleRight();
void handleStop();
void handleSpeed();
void handleJoystick();
void handleProfile();
void handleNotFound();
void updateCommandTimer();
void handleEmergencyStop();

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
    updateCommandTimer();

    logInfo("[REMOTE] Forward");

    executeMotion(MOTION_FORWARD);

    server.send(200, "text/plain", "OK");
}

void handleBackward()
{
    updateCommandTimer();

    logInfo("[REMOTE] Backward");

    executeMotion(MOTION_BACKWARD);

    server.send(200, "text/plain", "OK");
}

void handleLeft()
{
    updateCommandTimer();

    logInfo("[REMOTE] Left");

    executeMotion(MOTION_LEFT);

    server.send(200, "text/plain", "OK");
}

void handleRight()
{
    updateCommandTimer();

    logInfo("[REMOTE] Right");

    executeMotion(MOTION_RIGHT);

    server.send(200, "text/plain", "OK");
}

void handleStop()
{
    updateCommandTimer();

    logInfo("[REMOTE] Stop");

    executeMotion(MOTION_STOP);

    server.send(200, "text/plain", "OK");
}

void handleSpeed()
{
    if (!server.hasArg("value"))
    {
        server.send(
            400,
            "text/plain",
            "Missing speed value"
        );

        return;
    }

    int speed = server.arg("value").toInt();

    if (speed < 0)
    {
        speed = 0;
    }

    if (speed > 255)
    {
        speed = 255;
    }

    setMotionSpeed(speed);

    logInfo(
        "[REMOTE] Speed Changed: " +
        String(speed)
    );

    server.send(
        200,
        "text/plain",
        "OK"
    );
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

void updateCommandTimer()
{
    lastCommandTime = millis();

    timeoutTriggered = false;
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

    server.on(
        "/estop",
        HTTP_GET,
        handleEmergencyStop
    );

    server.on("/speed", HTTP_GET, handleSpeed);

    server.on("/joystick", HTTP_GET, handleJoystick);

    server.on("/profile", HTTP_GET, handleProfile);

    server.onNotFound(handleNotFound);

    server.begin();

    logInfo("[REMOTE] HTTP Server Started");

    lastCommandTime = millis();
}

void handleRemoteControl()
{
    server.handleClient();

    if (
        !timeoutTriggered &&
        millis() - lastCommandTime > COMMAND_TIMEOUT
    )
    {
        logInfo(
            "[SAFETY] Motion Timeout"
        );

        executeMotion(
            MOTION_STOP
        );

        timeoutTriggered = true;
    }
}

void handleJoystick()
{
    updateCommandTimer();

    if (!server.hasArg("x") || !server.hasArg("y"))
    {
        server.send(
            400,
            "text/plain",
            "Missing joystick values"
        );

        return;
    }

    int steering = server.arg("x").toInt();
    int throttle = server.arg("y").toInt();

    steering = constrain(steering, -255, 255);
    throttle = constrain(throttle, -255, 255);

    executeJoystick(
        steering,
        throttle
    );

    server.send(
        200,
        "text/plain",
        "OK"
    );
}


void handleProfile()
{
    updateCommandTimer();

    if (!server.hasArg("mode"))
    {
        server.send(
            400,
            "text/plain",
            "Missing profile"
        );

        return;
    }

    String mode =
        server.arg("mode");

    if (mode == "precision")
    {
        setMotionProfile(
            PROFILE_PRECISION
        );
    }
    else if (mode == "normal")
    {
        setMotionProfile(
            PROFILE_NORMAL
        );
    }
    else if (mode == "sport")
    {
        setMotionProfile(
            PROFILE_SPORT
        );
    }
    else
    {
        server.send(
            400,
            "text/plain",
            "Invalid profile"
        );

        return;
    }

    MotionProfile profile =
        getMotionProfile();

    setMotionSpeed(
        profile.defaultSpeed
    );

    server.send(
        200,
        "text/plain",
        "OK"
    );
}

void handleEmergencyStop()
{
    updateCommandTimer();

    logInfo("[SAFETY] Emergency Stop");

    executeMotion(MOTION_STOP);

    server.send(
        200,
        "text/plain",
        "OK"
    );
}