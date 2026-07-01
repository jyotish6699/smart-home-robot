#include <Arduino.h>

#include "motor_driver.h"
#include "logger.h"

/*
 * -------------------------
 * L298N Pin Configuration
 * -------------------------
 */

constexpr uint8_t ENA = 25;

constexpr uint8_t IN1 = 26;
constexpr uint8_t IN2 = 27;

constexpr uint8_t IN3 = 14;
constexpr uint8_t IN4 = 12;

constexpr uint8_t ENB = 13;

/*
 * -------------------------
 * PWM Configuration
 * -------------------------
 */

constexpr uint8_t LEFT_CHANNEL = 0;
constexpr uint8_t RIGHT_CHANNEL = 1;

constexpr uint32_t PWM_FREQUENCY = 1000;
constexpr uint8_t PWM_RESOLUTION = 8;

/*
 * -------------------------
 * Utility
 * -------------------------
 */

static uint8_t clampPWM(int16_t value)
{
    if (value < 0)
    {
        value = -value;
    }

    if (value > 255)
    {
        value = 255;
    }

    return (uint8_t)value;
}

static void applyLeftMotor(int16_t speed)
{
    uint8_t pwm = clampPWM(speed);

    if (speed > 0)
    {
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
    }
    else if (speed < 0)
    {
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);
    }
    else
    {
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, LOW);
    }

    ledcWrite(LEFT_CHANNEL, pwm);
}

static void applyRightMotor(int16_t speed)
{
    uint8_t pwm = clampPWM(speed);

    if (speed > 0)
    {
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, LOW);
    }
    else if (speed < 0)
    {
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, HIGH);
    }
    else
    {
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, LOW);
    }

    ledcWrite(RIGHT_CHANNEL, pwm);
}

/*
 * -------------------------
 * Public API
 * -------------------------
 */

void setupMotors()
{
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);

    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);

    ledcSetup(
        LEFT_CHANNEL,
        PWM_FREQUENCY,
        PWM_RESOLUTION
    );

    ledcSetup(
        RIGHT_CHANNEL,
        PWM_FREQUENCY,
        PWM_RESOLUTION
    );

    ledcAttachPin(
        ENA,
        LEFT_CHANNEL
    );

    ledcAttachPin(
        ENB,
        RIGHT_CHANNEL
    );

    setMotorOutput(0, 0);

    logInfo("[MOTOR] Driver Ready");
}

void setMotorOutput(
    int16_t leftSpeed,
    int16_t rightSpeed
)
{
    applyLeftMotor(leftSpeed);

    applyRightMotor(rightSpeed);
}