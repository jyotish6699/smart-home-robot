const SPEED_PRESET = {

    PRECISION:80,

    NORMAL:180,

    SPORT:255

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

        await fetch(`/speed?value=${value}`);
    }

    slider.addEventListener("input", () => {

        setSpeed(slider.value);

    });

    document.getElementById("precision")
        .onclick = () => setSpeed(SPEED_PRESET.PRECISION);

    document.getElementById("normal")
        .onclick = () => setSpeed(SPEED_PRESET.NORMAL);

    document.getElementById("sport")
        .onclick = () => setSpeed(SPEED_PRESET.SPORT);
}