#include "motion_engine.h"

#include "motor_driver.h"
#include "logger.h"

void setupMotionEngine()
{
    logInfo("[MOTION] Motion Engine Ready");
}

void executeMotion(MotionCommand command)
{
    switch (command)
    {
        case MOTION_FORWARD:

            moveForward();

            break;

        case MOTION_BACKWARD:

            moveBackward();

            break;

        case MOTION_LEFT:

            turnLeft();

            break;

        case MOTION_RIGHT:

            turnRight();

            break;

        case MOTION_SPIN_LEFT:

            turnLeft();

            break;

        case MOTION_SPIN_RIGHT:

            turnRight();

            break;

        case MOTION_STOP:
        default:

            stopMotors();

            break;
    }
}