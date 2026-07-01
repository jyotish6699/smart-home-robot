#include <Arduino.h>

#include <WiFi.h>
#include <WebServer.h>

#include <LittleFS.h>

#include "remote_control.h"
#include "motion_engine.h"
#include "motion_profile.h"
#include "logger.h"
#include "wifi_manager.h"

/*
 * ------------------------------------
 * HTTP Server
 * ------------------------------------
 */

WebServer server(80);

/*
 * ------------------------------------
 * Motion Safety
 * ------------------------------------
 */

constexpr unsigned long COMMAND_TIMEOUT = 500;

static unsigned long lastCommandTime = 0;

static bool timeoutTriggered = false;

static bool emergencyStopped = false;

/*
 * ------------------------------------
 * Forward Declarations
 * ------------------------------------
 */

void handleForward();

void handleBackward();

void handleLeft();

void handleRight();

void handleStop();

void handleEmergencyStop();

void handleSpeed();

void handleProfile();

void handleJoystick();

void handleNotFound();

void updateCommandTimer();

bool serveFile(String path);

String getContentType(
    const String &filename
);

/*
 * ------------------------------------
 * Content Type
 * ------------------------------------
 */

String getContentType(
    const String &filename
)
{
    if (filename.endsWith(".html"))
        return "text/html";

    if (filename.endsWith(".css"))
        return "text/css";

    if (filename.endsWith(".js"))
        return "application/javascript";

    return "text/plain";
}

/*
 * ------------------------------------
 * LittleFS File Server
 * ------------------------------------
 */

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

    File file =
        LittleFS.open(
            path,
            "r"
        );

    server.streamFile(
        file,
        getContentType(path)
    );

    file.close();

    return true;
}


/*
 * ------------------------------------
 * Utilities
 * ------------------------------------
 */

void updateCommandTimer()
{
    lastCommandTime = millis();

    timeoutTriggered = false;
}

/*
 * ------------------------------------
 * Motion Commands
 * ------------------------------------
 */

void handleForward()
{
    updateCommandTimer();

    logInfo(
        "[REMOTE] Forward " +
        String(millis())
    );

    executeMotion(
        MOTION_FORWARD
    );

    server.send(
        200,
        "text/plain",
        "OK"
    );
}

void handleBackward()
{
    updateCommandTimer();

    logInfo("[REMOTE] Backward");

    executeMotion(
        MOTION_BACKWARD
    );

    server.send(
        200,
        "text/plain",
        "OK"
    );
}

void handleLeft()
{
    updateCommandTimer();

    logInfo("[REMOTE] Left");

    executeMotion(
        MOTION_LEFT
    );

    server.send(
        200,
        "text/plain",
        "OK"
    );
}

void handleRight()
{
    updateCommandTimer();

    logInfo("[REMOTE] Right");

    executeMotion(
        MOTION_RIGHT
    );

    server.send(
        200,
        "text/plain",
        "OK"
    );
}

void handleStop()
{
    updateCommandTimer();

    logInfo("[REMOTE] Stop");

    executeMotion(
        MOTION_STOP
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

    logInfo(
        "[SAFETY] Emergency Stop"
    );

    executeMotion(
        MOTION_STOP
    );

    server.send(
        200,
        "text/plain",
        "OK"
    );
}

/*
 * ------------------------------------
 * Speed
 * ------------------------------------
 */

void handleSpeed()
{
    updateCommandTimer();

    if (!server.hasArg("value"))
    {
        server.send(
            400,
            "text/plain",
            "Missing speed value"
        );

        return;
    }

    int speed =
        server.arg("value").toInt();

    speed =
        constrain(
            speed,
            0,
            255
        );

    setMotionSpeed(speed);

    logInfo(
        "[REMOTE] Speed = " +
        String(speed)
    );

    server.send(
        200,
        "text/plain",
        "OK"
    );
}

/*
 * ------------------------------------
 * Motion Profiles
 * ------------------------------------
 */

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

    logInfo(
        "[PROFILE] " + mode
    );

    server.send(
        200,
        "text/plain",
        "OK"
    );
}

/*
 * ------------------------------------
 * Virtual Joystick
 * ------------------------------------
 */

void handleJoystick()
{
    updateCommandTimer();

    if (
        !server.hasArg("x") ||
        !server.hasArg("y")
    )
    {
        server.send(
            400,
            "text/plain",
            "Missing joystick values"
        );

        return;
    }

    int steering =
        constrain(
            server.arg("x").toInt(),
            -255,
            255
        );

    int throttle =
        constrain(
            server.arg("y").toInt(),
            -255,
            255
        );

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

/*
 * ------------------------------------
 * 404 Handler
 * ------------------------------------
 */

void handleNotFound()
{
    if (server.uri() == "/favicon.ico")
    {
        server.send(204);

        return;
    }

    if (serveFile(server.uri()))
    {
        return;
    }

    logInfo(
        "[HTTP] 404 : " +
        server.uri()
    );

    server.send(
        404,
        "text/plain",
        "404 Not Found"
    );
}

/*
 * ------------------------------------
 * Remote Control Setup
 * ------------------------------------
 */

void setupRemoteControl()
{
    if (!LittleFS.begin())
    {
        logInfo(
            "[REMOTE] LittleFS Mount Failed"
        );

        return;
    }

    logInfo(
        "[REMOTE] LittleFS Ready"
    );

    server.on(
        "/",
        HTTP_GET,
        []()
        {
            serveFile("/index.html");
        }
    );

    /*
     * Motion
     */

    server.on(
        "/forward",
        HTTP_GET,
        handleForward
    );

    server.on(
        "/backward",
        HTTP_GET,
        handleBackward
    );

    server.on(
        "/left",
        HTTP_GET,
        handleLeft
    );

    server.on(
        "/right",
        HTTP_GET,
        handleRight
    );

    server.on(
        "/stop",
        HTTP_GET,
        handleStop
    );

    server.on(
        "/joystick",
        HTTP_GET,
        handleJoystick
    );

    /*
     * Speed
     */

    server.on(
        "/speed",
        HTTP_GET,
        handleSpeed
    );

    /*
     * Motion Profile
     */

    server.on(
        "/profile",
        HTTP_GET,
        handleProfile
    );

    /*
     * Safety
     */

    server.on(
        "/estop",
        HTTP_GET,
        handleEmergencyStop
    );

    /*
     * Static Files
     */

    server.onNotFound(
        handleNotFound
    );

    server.begin();

    lastCommandTime = millis();

    logInfo(
        "[REMOTE] HTTP Server Started"
    );
}

/*
 * ------------------------------------
 * Remote Control Loop
 * ------------------------------------
 */

void handleRemoteControl()
{
    server.handleClient();

    /*
     * WiFi Safety
     */

    if (!isWiFiConnected())
    {
        if (!emergencyStopped)
        {
            logInfo(
                "[SAFETY] WiFi Lost"
            );

            executeMotion(
                MOTION_STOP
            );

            emergencyStopped = true;
        }

        return;
    }

    emergencyStopped = false;

    /*
     * Command Timeout
     */

    if (
        timeoutTriggered
    )
    {
        return;
    }

    if (
        millis() - lastCommandTime <
        COMMAND_TIMEOUT
    )
    {
        return;
    }

    timeoutTriggered = true;

    executeMotion(
        MOTION_STOP
    );

    logInfo(
        "[SAFETY] Motion Timeout"
    );
}