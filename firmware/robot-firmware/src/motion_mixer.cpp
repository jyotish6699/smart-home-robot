#include "motion_mixer.h"

#include <Arduino.h>

MotionOutput mixMotion(
    int steering,
    int throttle
)
{
    MotionOutput output;

    output.left =
        throttle + steering;

    output.right =
        throttle - steering;

    output.left =
        constrain(
            output.left,
            -255,
            255
        );

    output.right =
        constrain(
            output.right,
            -255,
            255
        );

    return output;
}