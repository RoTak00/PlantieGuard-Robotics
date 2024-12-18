#ifndef SENSORS_H
#define SENSORS_H

#include <Arduino.h>
#include <HTU2xD_SHT2x_Si70xx.h>
class PG_Sensors
{
public:
    PG_Sensors();

    void test();
    String getURLEncodedData();

private:
    const uint8_t MOISTURE_PIN = A0;

    const uint16_t MOISTURE_UPPER_DRY = 500;
    const uint16_t MOISTURE_LOWER_WET = 200;

    const uint8_t MT_SENSOR_ADDRESS = 0x40;

    HTU2xD_SHT2x_SI70xx *mt_sensor = NULL;

private:
    float getHumidity(uint8_t *error);
    float getSoilHumidity(uint8_t *error);
    float getTemperature(uint8_t *error);
};

#endif