#include <Arduino.h>

#include "motor_driver.h"
#include "logger.h"

#define ENA 25
#define IN1 26
#define IN2 27

#define IN3 14
#define IN4 12
#define ENB 13

void setupMotors()
{
    pinMode(ENA, OUTPUT);

    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);

    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);

    pinMode(ENB, OUTPUT);

    digitalWrite(ENA, HIGH);
    digitalWrite(ENB, HIGH);

    stopMotors();

    logInfo("[MOTOR] Driver Ready");
}

void moveForward()
{
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);

    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
}

void moveBackward()
{
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);

    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
}

void turnLeft()
{
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);

    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
}

void turnRight()
{
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);

    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
}

void stopMotors()
{
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);

    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
}