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