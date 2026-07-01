import { apiFast } from "./api.js";

/*
 * ------------------------------------
 * Button Controls
 * ------------------------------------
 */

function send(command)
{
    api("/" + command);
}

function bind(id, command)
{
    const button =
        document.getElementById(id);

    if (!button)
    {
        console.error(
            "[CONTROLS] Missing button:",
            id
        );

        return;
    }

    /*
     * Desktop
     */

    button.addEventListener(
        "mousedown",
        () =>
        {
            send(command);
        }
    );

    button.addEventListener(
        "mouseup",
        () =>
        {
            send("stop");
        }
    );

    button.addEventListener(
        "mouseleave",
        () =>
        {
            send("stop");
        }
    );

    /*
     * Mobile
     */

    button.addEventListener(
        "touchstart",
        (event) =>
        {
            event.preventDefault();

            send(command);
        },
        {
            passive: false
        }
    );

    button.addEventListener(
        "touchend",
        (event) =>
        {
            event.preventDefault();

            send("stop");
        },
        {
            passive: false
        }
    );

    /*
     * Safety
     */

    button.addEventListener(
        "touchcancel",
        () =>
        {
            send("stop");
        }
    );
}

export function initControls()
{
    bind(
        "forward",
        "forward"
    );

    bind(
        "backward",
        "backward"
    );

    bind(
        "left",
        "left"
    );

    bind(
        "right",
        "right"
    );

    bind(
        "stop",
        "stop"
    );

    console.log(
        "[CONTROLS] Ready"
    );
}