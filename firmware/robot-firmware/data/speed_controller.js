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
        document.getElementById("speedSlider");

    const text =
        document.getElementById("speedText");

    async function setSpeed(value)
    {
        slider.value = value;

        text.textContent = value;

        try
        {
            await fetch(
                `/speed?value=${value}`
            );
        }
        catch(err)
        {
            console.error(err);
        }
    }

    async function changeProfile(profile)
    {
        try
        {
            await fetch(
                `/profile?mode=${profile.name}`
            );

            slider.value =
                profile.speed;

            text.textContent =
                profile.speed;
        }
        catch(err)
        {
            console.error(err);
        }
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

    document
        .getElementById("precision")
        .addEventListener(
            "click",
            () =>
            {
                changeProfile(
                    PROFILE.precision
                );
            }
        );

    document
        .getElementById("normal")
        .addEventListener(
            "click",
            () =>
            {
                changeProfile(
                    PROFILE.normal
                );
            }
        );

    document
        .getElementById("sport")
        .addEventListener(
            "click",
            () =>
            {
                changeProfile(
                    PROFILE.sport
                );
            }
        );
}