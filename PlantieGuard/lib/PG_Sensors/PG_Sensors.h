#ifndef SENSORS_H
#define SENSORS_H

#include <Arduino.h>
class PG_Sensors
{
public:
    PG_Sensors();

private:
    const uint8_t MOISTURE_PIN = A0;

    const uint8_t MOISTURE_UPPER_DRY = 480;
    const uint8_t MOISTURE_LOWER_WET = 200;
};

#endif