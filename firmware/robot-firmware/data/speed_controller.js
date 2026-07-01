import { api } from "./api.js";

/*
 * ------------------------------------
 * Motion Profiles
 * ------------------------------------
 */

const PROFILE = {

    precision: {

        speed: 80,

        name: "precision"

    },

    normal: {

        speed: 180,

        name: "normal"

    },

    sport: {

        speed: 255,

        name: "sport"

    }

};

export function initSpeedController()
{
    const slider =
        document.getElementById(
            "speedSlider"
        );

    const text =
        document.getElementById(
            "speedText"
        );

    const precision =
        document.getElementById(
            "precision"
        );

    const normal =
        document.getElementById(
            "normal"
        );

    const sport =
        document.getElementById(
            "sport"
        );

    if (
        !slider ||
        !text ||
        !precision ||
        !normal ||
        !sport
    )
    {
        console.error(
            "[SPEED] Missing Elements"
        );

        return;
    }

    function updateUI(value)
    {
        slider.value = value;

        text.textContent = value;
    }

    async function setSpeed(value)
    {
        updateUI(value);

        await api(
            `/speed?value=${value}`
        );
    }

    function setActiveButton(button)
    {
        [
            precision,
            normal,
            sport
        ].forEach(
            (b) =>
            {
                b.classList.remove(
                    "active"
                );
            }
        );

        button.classList.add(
            "active"
        );
    }

    async function changeProfile(profile, button)
    {
        const ok =
            await api(
                `/profile?mode=${profile.name}`
            );

        if (!ok)
        {
            return;
        }

        updateUI(
            profile.speed
        );

        setActiveButton(
            button
        );
    }

    slider.addEventListener(
        "input",
        () =>
        {
            setSpeed(
                slider.value
            );
        }
    );

    precision.addEventListener(
        "click",
        () =>
        {
            changeProfile(
                PROFILE.precision,
                precision
            );
        }
    );

    normal.addEventListener(
        "click",
        () =>
        {
            changeProfile(
                PROFILE.normal,
                normal
            );
        }
    );

    sport.addEventListener(
        "click",
        () =>
        {
            changeProfile(
                PROFILE.sport,
                sport
            );
        }
    );

    setActiveButton(
        sport
    );

    console.log(
        "[SPEED] Ready"
    );
}