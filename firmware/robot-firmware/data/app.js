function send(command)
{
    fetch("/" + command);
}

function bind(id, command)
{
    const button = document.getElementById(id);

    button.addEventListener(
        "mousedown",
        () => send(command)
    );

    button.addEventListener(
        "mouseup",
        () => send("stop")
    );

    button.addEventListener(
        "mouseleave",
        () => send("stop")
    );

    button.addEventListener(
        "touchstart",
        (e) =>
        {
            e.preventDefault();

            send(command);
        }
    );

    button.addEventListener(
        "touchend",
        (e) =>
        {
            e.preventDefault();

            send("stop");
        }
    );
}

bind("forward","forward");
bind("backward","backward");
bind("left","left");
bind("right","right");
bind("stop","stop");

const speedSlider =
    document.getElementById("speedSlider");

const speedText =
    document.getElementById("speedText");

speedSlider.addEventListener("input", async () => {

    const value = speedSlider.value;

    speedText.textContent = value;

    try {

        await fetch(`/speed?value=${value}`);

    }
    catch (err) {

        console.error(err);

    }

});

function setSpeed(value)
{
    speedSlider.value = value;

    speedText.textContent = value;

    fetch(`/speed?value=${value}`);
}

document
    .getElementById("precision")
    .onclick = () => setSpeed(80);

document
    .getElementById("normal")
    .onclick = () => setSpeed(180);

document
    .getElementById("sport")
    .onclick = () => setSpeed(255);