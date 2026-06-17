#include <Arduino.h>

void setup()
{
    Serial.begin(115200);

    Serial.println("================================");
    Serial.println("SMART HOME ROBOT");
    Serial.println("Version: v0.0.2");
    Serial.println("ESP32 Boot Successful");
    Serial.println("================================");
}

void loop()
{
    Serial.println("Robot Running...");

    delay(1000);
}