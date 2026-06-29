import { initControls } from "./controls.js";
import { initSpeedController } from "./speed_controller.js";
import { initModeSelector } from "./mode_selector.js";
import { initJoystick } from "./joystick.js";

window.addEventListener("DOMContentLoaded", () => {

    initControls();

    initSpeedController();

    initModeSelector();

    initJoystick();

    document
        .getElementById("emergencyStop")
        .addEventListener(
            "click",
            async () =>
            {
                await fetch("/estop");
            }
        );

});