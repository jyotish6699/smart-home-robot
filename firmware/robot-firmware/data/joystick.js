const JOYSTICK_RADIUS = 75;

let dragging = false;

let lastX = 0;

let lastY = 0;

async function sendJoystick(x,y)
{
    if(
        x===lastX &&
        y===lastY
    )
    {
        return;
    }

    lastX = x;

    lastY = y;

    await fetch(`/joystick?x=${x}&y=${y}`);
}

export function initJoystick()
{
    const base =
        document.getElementById("joystickBase");

    const stick =
        document.getElementById("joystickStick");

    stick.addEventListener("pointerdown", () => {

        dragging = true;

    });

    document.addEventListener("pointerup", () => {

        if(!dragging)
            return;

        dragging = false;

        stick.style.transform =
            "translate(0px,0px)";

        sendJoystick(0,0);

    });

    document.addEventListener("pointermove",(event)=>{

        if(!dragging)
            return;

        const rect =
            base.getBoundingClientRect();

        const cx =
            rect.left + rect.width/2;

        const cy =
            rect.top + rect.height/2;

        let dx =
            event.clientX - cx;

        let dy =
            event.clientY - cy;

        const dist =
            Math.sqrt(dx*dx+dy*dy);

        if(dist>JOYSTICK_RADIUS)
        {
            dx = dx/dist*JOYSTICK_RADIUS;

            dy = dy/dist*JOYSTICK_RADIUS;
        }

        stick.style.transform =
            `translate(${dx}px,${dy}px)`;

        const steering =
            Math.round(dx/JOYSTICK_RADIUS*255);

        const throttle =
            Math.round(-dy/JOYSTICK_RADIUS*255);

        sendJoystick(
            steering,
            throttle
        );

    });
}