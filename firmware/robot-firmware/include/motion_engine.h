#ifndef MOTION_ENGINE_H
#define MOTION_ENGINE_H

#include <stdint.h>

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

void setMotionSpeed(uint8_t speed);

void executeJoystick(
    int16_t steering,
    int16_t throttle
);

uint8_t getMotionSpeed();

#endif