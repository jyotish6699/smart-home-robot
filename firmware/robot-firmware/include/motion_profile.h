#ifndef MOTION_PROFILE_H
#define MOTION_PROFILE_H

#include <stdint.h>

enum MotionProfileType
{
    PROFILE_PRECISION,

    PROFILE_NORMAL,

    PROFILE_SPORT
};

struct MotionProfile
{
    uint8_t maxSpeed;

    uint8_t defaultSpeed;

    uint8_t acceleration;

    uint8_t turnSensitivity;
};

void setupMotionProfile();

void setMotionProfile(
    MotionProfileType profile
);

MotionProfile getMotionProfile();

MotionProfileType getMotionProfileType();

#endif