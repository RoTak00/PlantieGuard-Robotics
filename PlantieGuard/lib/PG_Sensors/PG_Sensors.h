#ifndef SENSORS_H
#define SENSORS_H

#include <Arduino.h>
#include <HTU2xD_SHT2x_Si70xx.h>
class PG_Sensors
{
public:
    PG_Sensors();

    void test();

private:
    const uint8_t MOISTURE_PIN = A0;

    const uint8_t MOISTURE_UPPER_DRY = 480;
    const uint8_t MOISTURE_LOWER_WET = 200;

    const uint8_t MT_SENSOR_ADDRESS = 0x40;

    HTU2xD_SHT2x_SI70xx *mt_sensor = NULL;
};

#endif