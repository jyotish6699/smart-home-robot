#ifndef MOTION_ENGINE_H
#define MOTION_ENGINE_H

enum MotionCommand
{
    MOTION_STOP,

    MOTION_FORWARD,
    MOTION_BACKWARD,

    MOTION_LEFT,
    MOTION_RIGHT,

    MOTION_SPIN_LEFT,
    MOTION_SPIN_RIGHT
};

void setupMotionEngine();

void executeMotion(MotionCommand command);

#endif