#ifndef LOGGER_H
#define LOGGER_H

#include <Arduino.h>

void logInfo(const String &message);

String getLogHistory();

#endif