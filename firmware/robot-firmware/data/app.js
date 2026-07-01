/*
 * ------------------------------------
 * Aegis Remote Control
 * ------------------------------------
 */

import { api } from "./api.js";

import { initControls } from "./controls.js";
import { initJoystick } from "./joystick.js";
import { initSpeedController } from "./speed_controller.js";
import { initModeSelector } from "./mode_selector.js";

window.addEventListener(
    "DOMContentLoaded",
    () =>
    {
        console.log(
            "[APP] Initializing..."
        );

        initControls();

        initJoystick();

        initSpeedController();

        initModeSelector();

        initEmergencyStop();

        initConnectionMonitor();

        console.log(
            "[APP] Ready"
        );
    }
);

/*
 * ------------------------------------
 * Emergency Stop
 * ------------------------------------
 */

function initEmergencyStop()
{
    const button =
        document.getElementById(
            "emergencyStop"
        );

    if (!button)
    {
        console.error(
            "[APP] Emergency Stop Missing"
        );

        return;
    }

    button.addEventListener(
        "click",
        async () =>
        {
            const ok =
                await api(
                    "/estop"
                );

            if (!ok)
            {
                console.error(
                    "[APP] Emergency Stop Failed"
                );
            }
        }
    );
}

/*
 * ------------------------------------
 * Connection Status
 * ------------------------------------
 */

function initConnectionMonitor()
{
    const status =
        document.getElementById(
            "connectionStatus"
        );

    if (!status)
    {
        return;
    }

    function setConnected()
    {
        status.textContent =
            "🟢 Connected";
    }

    function setDisconnected()
    {
        status.textContent =
            "🔴 Disconnected";
    }

    window.addEventListener(
        "online",
        setConnected
    );

    window.addEventListener(
        "offline",
        setDisconnected
    );

    if (navigator.onLine)
    {
        setConnected();
    }
    else
    {
        setDisconnected();
    }
}