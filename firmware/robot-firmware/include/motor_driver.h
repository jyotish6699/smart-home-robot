#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H

#include <stdint.h>

void setupMotors();

/*
 * Left Speed
 * ------------
 * +255 = Full Forward
 *    0 = Stop
 * -255 = Full Reverse
 *
 * Right Speed
 * ------------
 * +255 = Full Forward
 *    0 = Stop
 * -255 = Full Reverse
 */
void setMotorOutput(
    int16_t leftSpeed,
    int16_t rightSpeed
);

#endif