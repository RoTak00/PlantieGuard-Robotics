#include <Arduino.h>
#include <PG_Sensors.h>
#include <HTU2xD_SHT2x_Si70xx.h>
#include <Serial.h>

PG_Sensors::PG_Sensors()
{
    pinMode(MOISTURE_PIN, INPUT);
    mt_sensor = new HTU2xD_SHT2x_SI70xx(HTU2xD_SENSOR, HUMD_12BIT_TEMP_14BIT);

    while (mt_sensor->begin() != true) // reset sensor, set heater off, set resolution, check power (sensor doesn't operate correctly if VDD < +2.25v)
    {
        Serial.println(F("HTU2xD/SHT2x not connected, fail or VDD < +2.25v")); //(F()) save string to flash & keeps dynamic memory free

        delay(5000);
    }

    Serial.println(F("HTU2xD/SHT2x OK"));
}

void PG_Sensors::test()
{

    float htValue = mt_sensor->readTemperature(); // accuracy +-0.3C in range 0C..60C at 14-bit

    Serial.print(F("Temperature...............: "));

    if (htValue != HTU2XD_SHT2X_SI70XX_ERROR) // HTU2XD_SHT2X_SI70XX_ERROR = 255, library returns 255 if error occurs
    {
        Serial.print(htValue);
        Serial.println(F(" +-0.3C"));
    }
    else
    {
        Serial.println(F("<error>"));

        mt_sensor->softReset();                          // last chance to make it alive, all registers (except heater bit) will set to default
        mt_sensor->setHeater(false);                     // true=heater on, false=heater off
        mt_sensor->setResolution(HUMD_12BIT_TEMP_14BIT); // humidity 12-bit, temperature 14-bit
    }

    /* read compensated humidity */
    delay(500); // measurement with high frequency leads to heating of the sensor, see NOTE

    Serial.print(F("Compensated Humidity......: "));

    if (htValue != HTU2XD_SHT2X_SI70XX_ERROR) // if temperature OK, measure RH & calculate compensated humidity
    {
        htValue = mt_sensor->getCompensatedHumidity(htValue); // accuracy +-2% in range 0%..100%/0C..80C at 12-bit, to compensates influence of T on RH

        if (htValue != HTU2XD_SHT2X_SI70XX_ERROR)
        {
            Serial.print(htValue);
            Serial.println(F(" +-2%"));
        }
    }
    if (htValue == HTU2XD_SHT2X_SI70XX_ERROR)
    {
        Serial.println(F("<error>"));
    }

    /* read humidity */
    delay(500); // measurement with high frequency leads to heating of the sensor, see NOTE

    htValue = mt_sensor->readHumidity(); // accuracy +-2% in range 20%..80%/25C at 12-bit

    Serial.print(F("Humidity..................: "));

    if (htValue != HTU2XD_SHT2X_SI70XX_ERROR)
    {
        Serial.print(htValue);
        Serial.println(F(" +-2%"));
    }
    else
    {
        Serial.println(F("<error>"));
    }

    /* read power status */
    Serial.print(F("Power.....................: "));

    if (mt_sensor->voltageStatus() == true)
    {
        Serial.println(F("power OK, VDD > +2.25v"));
    }
    else
    {
        Serial.println(F("power FAIL, VDD < +2.25v"));
    }

    /* read device ID */
    Serial.print(F("Sensor ID.................: "));

    htValue = mt_sensor->readDeviceID(); // return 21, 7021, 7020, 7013, 7006 & 7000 for Si70xx engineering samples

    if (htValue != HTU2XD_SHT2X_SI70XX_ERROR)
    {
        Serial.println(htValue);
    }
    else
    {
        Serial.println(F("<error>"));
    }

    /* read FW version */
    Serial.print(F("Sensor FW.................: "));

    htValue = mt_sensor->readFirmwareVersion(); // return 1=v1.0, 2=v2.0

    if (htValue != HTU2XD_SHT2X_SI70XX_ERROR)
    {
        Serial.print(F("v"));
        Serial.println(htValue);
    }
    else
    {
        Serial.println(F("<error>"));
    }
}
