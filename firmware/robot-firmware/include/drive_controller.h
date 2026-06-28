#ifndef DRIVE_CONTROLLER_H
#define DRIVE_CONTROLLER_H

#include <stdint.h>

void setupDriveController();

void setDriveSpeed(uint8_t speed);

uint8_t getDriveSpeed();

void driveForward();

void driveBackward();

void driveLeft();

void driveRight();

void driveSpinLeft();

void driveSpinRight();

void driveStop();

#endif