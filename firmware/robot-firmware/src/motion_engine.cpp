#include "motion_engine.h"

#include "drive_controller.h"
#include "logger.h"
#include "motion_mixer.h"
#include "motion_profile.h"

void setupMotionEngine()
{
    setupDriveController();

    setDriveSpeed(255);

    logInfo("[MOTION] Motion Engine Ready");
}

void setMotionSpeed(uint8_t speed)
{
    setDriveSpeed(speed);

    logInfo(
        "[MOTION] Speed = " +
        String(speed)
    );
}

uint8_t getMotionSpeed()
{
    return getDriveSpeed();
}

void executeMotion(MotionCommand command)
{
    switch (command)
    {
        case MOTION_FORWARD:

            driveForward();

            break;

        case MOTION_BACKWARD:

            driveBackward();

            break;

        case MOTION_LEFT:

            driveLeft();

            break;

        case MOTION_RIGHT:

            driveRight();

            break;

        case MOTION_SPIN_LEFT:

            driveSpinLeft();

            break;

        case MOTION_SPIN_RIGHT:

            driveSpinRight();

            break;

        case MOTION_STOP:
        default:

            driveStop();

            break;
    }
}

void executeJoystick(
    int16_t steering,
    int16_t throttle
)
{
    MotionProfile profile =
        getMotionProfile();

    throttle =
        map(
            throttle,
            -255,
            255,
            -profile.maxSpeed,
            profile.maxSpeed
        );

    steering =
        map(
            steering,
            -255,
            255,
            -profile.turnSensitivity,
            profile.turnSensitivity
        );

    MotionOutput output =
        mixMotion(
            steering,
            throttle
        );

    driveJoystick(
        output.left,
        output.right
    );

    logInfo(
        "[JOYSTICK] "
        "P=" + String(getMotionProfileType()) +
        " T=" + String(throttle) +
        " S=" + String(steering) +
        " L=" + String(output.left) +
        " R=" + String(output.right)
    );
}

