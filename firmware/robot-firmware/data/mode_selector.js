/*
 * ------------------------------------
 * Driving Mode Selector
 * ------------------------------------
 */

export function initModeSelector()
{
    const buttonMode =
        document.getElementById(
            "buttonMode"
        );

    const joystickMode =
        document.getElementById(
            "joystickMode"
        );

    const buttonControls =
        document.getElementById(
            "buttonControls"
        );

    const joystickControls =
        document.getElementById(
            "joystickControls"
        );

    if (
        !buttonMode ||
        !joystickMode ||
        !buttonControls ||
        !joystickControls
    )
    {
        console.error(
            "[MODE] Missing Elements"
        );

        return;
    }

    function select(mode)
    {
        if (mode === "buttons")
        {
            buttonControls.classList.remove(
                "hidden"
            );

            joystickControls.classList.add(
                "hidden"
            );

            buttonMode.classList.add(
                "active"
            );

            joystickMode.classList.remove(
                "active"
            );
        }
        else
        {
            buttonControls.classList.add(
                "hidden"
            );

            joystickControls.classList.remove(
                "hidden"
            );

            joystickMode.classList.add(
                "active"
            );

            buttonMode.classList.remove(
                "active"
            );
        }

        localStorage.setItem(
            "driveMode",
            mode
        );
    }

    buttonMode.addEventListener(
        "click",
        () =>
        {
            select("buttons");
        }
    );

    joystickMode.addEventListener(
        "click",
        () =>
        {
            select("joystick");
        }
    );

    const savedMode =
        localStorage.getItem(
            "driveMode"
        );

    if (savedMode === "joystick")
    {
        select("joystick");
    }
    else
    {
        select("buttons");
    }

    console.log(
        "[MODE] Ready"
    );
}