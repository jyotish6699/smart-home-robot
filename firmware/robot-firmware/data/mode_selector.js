export function initModeSelector()
{
    const buttonMode =
        document.getElementById("buttonMode");

    const joystickMode =
        document.getElementById("joystickMode");

    const buttonControls =
        document.getElementById("buttonControls");

    const joystickControls =
        document.getElementById("joystickControls");

    function select(mode)
    {
        if(mode==="buttons")
        {
            buttonControls.classList.remove("hidden");

            joystickControls.classList.add("hidden");

            buttonMode.classList.add("active");

            joystickMode.classList.remove("active");
        }
        else
        {
            buttonControls.classList.add("hidden");

            joystickControls.classList.remove("hidden");

            joystickMode.classList.add("active");

            buttonMode.classList.remove("active");
        }
    }

    buttonMode.onclick = () => select("buttons");

    joystickMode.onclick = () => select("joystick");
}