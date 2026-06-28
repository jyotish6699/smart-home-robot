#include "motion_engine.h"

#include "drive_controller.h"
#include "logger.h"

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