#include "motion_engine.h"
#include "motor_driver.h"
#include "logger.h"

void setupMotionEngine()
{
    logInfo("[MOTION] Motion Engine Ready");
}

void motionForward()
{
    moveForward();
}

void motionBackward()
{
    moveBackward();
}

void motionLeft()
{
    turnLeft();
}

void motionRight()
{
    turnRight();
}

void motionStop()
{
    stopMotors();
}