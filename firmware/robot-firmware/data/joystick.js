import { apiFast } from "./api.js";

/*
 * ------------------------------------
 * Virtual Joystick
 * ------------------------------------
 */

const JOYSTICK_RADIUS = 75;

const UPDATE_INTERVAL = 15;   // ~40 updates/sec

let dragging = false;

let lastX = 0;
let lastY = 0;

let lastSend = 0;

function sendJoystick(x, y)
{
    const now = Date.now();

    if (now - lastSend < UPDATE_INTERVAL)
    {
        return;
    }

    lastSend = now;

    if (
        x === lastX &&
        y === lastY
    )
    {
        return;
    }

    lastX = x;
    lastY = y;

    apiFast(
        `/joystick?x=${x}&y=${y}`
    );
}

export function initJoystick()
{
    const base =
        document.getElementById(
            "joystickBase"
        );

    const stick =
        document.getElementById(
            "joystickStick"
        );

    if (!base || !stick)
    {
        console.error(
            "[JOYSTICK] Missing Elements"
        );

        return;
    }

    stick.addEventListener(
        "pointerdown",
        (event) =>
        {
            dragging = true;

            stick.setPointerCapture(
                event.pointerId
            );
        }
    );

    document.addEventListener(
        "pointerup",
        () =>
        {
            if (!dragging)
            {
                return;
            }

            dragging = false;

            stick.style.transform =
                "translate(0px,0px)";

            sendJoystick(
                0,
                0
            );
        }
    );

    document.addEventListener(
        "pointermove",
        (event) =>
        {
            if (!dragging)
            {
                return;
            }

            const rect =
                base.getBoundingClientRect();

            const centerX =
                rect.left +
                rect.width / 2;

            const centerY =
                rect.top +
                rect.height / 2;

            let dx =
                event.clientX - centerX;

            let dy =
                event.clientY - centerY;

            const distance =
                Math.sqrt(
                    dx * dx +
                    dy * dy
                );

            if (
                distance >
                JOYSTICK_RADIUS
            )
            {
                dx =
                    dx /
                    distance *
                    JOYSTICK_RADIUS;

                dy =
                    dy /
                    distance *
                    JOYSTICK_RADIUS;
            }

            stick.style.transform =
                `translate(${dx}px, ${dy}px)`;

            const steering =
                Math.round(
                    dx /
                    JOYSTICK_RADIUS *
                    255
                );

            const throttle =
                Math.round(
                    -dy /
                    JOYSTICK_RADIUS *
                    255
                );

            sendJoystick(
                steering,
                throttle
            );
        }
    );

    console.log(
        "[JOYSTICK] Ready"
    );
}