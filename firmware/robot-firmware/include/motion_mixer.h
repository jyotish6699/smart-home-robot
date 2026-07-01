#ifndef MOTION_MIXER_H
#define MOTION_MIXER_H

struct MotionOutput
{
    int left;
    int right;
};

MotionOutput mixMotion(
    int steering,
    int throttle
);

#endif