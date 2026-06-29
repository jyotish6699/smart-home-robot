#include "drive_controller.h"

#include "motor_driver.h"
#include "logger.h"

static uint8_t currentSpeed = 255;

static float steeringRatio = 0.50f;

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
    setMotorOutput(
        (int16_t)(speed() * steeringRatio),
        speed()
    );
}

void driveRight()
{
    setMotorOutput(
        speed(),
        (int16_t)(speed() * steeringRatio)
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

void driveJoystick(
    int16_t left,
    int16_t right
)
{
    int16_t maxValue =
        max(
            abs(left),
            abs(right)
        );

    if (maxValue > 255)
    {
        float scale =
            255.0f / maxValue;

        left =
            left * scale;

        right =
            right * scale;
    }

    left =
        constrain(
            left,
            -255,
            255
        );

    right =
        constrain(
            right,
            -255,
            255
        );

    setMotorOutput(
        left,
        right
    );
}