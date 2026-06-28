#include "drive_controller.h"

#include "motor_driver.h"
#include "logger.h"

static uint8_t currentSpeed = 255;

static inline int16_t speed()
{
    return (int16_t)currentSpeed;
}

void setupDriveController()
{
    currentSpeed = 255;

    logInfo("[DRIVE] Drive Controller Ready");
}

void setDriveSpeed(uint8_t speedValue)
{
    if (speedValue > 255)
    {
        speedValue = 255;
    }

    currentSpeed = speedValue;

    logInfo(
        "[DRIVE] Speed = " +
        String(currentSpeed)
    );
}

uint8_t getDriveSpeed()
{
    return currentSpeed;
}

void driveForward()
{
    setMotorOutput(
        speed(),
        speed()
    );
}

void driveBackward()
{
    setMotorOutput(
        -speed(),
        -speed()
    );
}

void driveLeft()
{
    /*
     * Soft Left Turn
     */

    setMotorOutput(
        speed() / 2,
        speed()
    );
}

void driveRight()
{
    /*
     * Soft Right Turn
     */

    setMotorOutput(
        speed(),
        speed() / 2
    );
}

void driveSpinLeft()
{
    /*
     * Rotate in Place
     */

    setMotorOutput(
        -speed(),
        speed()
    );
}

void driveSpinRight()
{
    /*
     * Rotate in Place
     */

    setMotorOutput(
        speed(),
        -speed()
    );
}

void driveStop()
{
    setMotorOutput(
        0,
        0
    );
}