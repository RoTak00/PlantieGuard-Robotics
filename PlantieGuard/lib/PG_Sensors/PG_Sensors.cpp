#include <Arduino.h>
#include <PG_Sensors.h>

PG_Sensors::PG_Sensors()
{
    pinMode(MOISTURE_PIN, INPUT);
}
