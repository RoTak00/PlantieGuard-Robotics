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

    Serial.print(F("Soil moisture..................:"));

    uint16_t soil_moisture_out = analogRead(MOISTURE_PIN);

    float val_a = soil_moisture_out - MOISTURE_LOWER_WET;
    float val_b = MOISTURE_UPPER_DRY - MOISTURE_LOWER_WET;

    float percentage_value = (1 - (float)val_a / val_b) * 100;

    Serial.print(percentage_value);

    Serial.println(F("%"));
}

float PG_Sensors::getHumidity(uint8_t *error)
{
    *error = 0;
    float htValue = mt_sensor->readHumidity(); // accuracy +-2% in range 20%..80%/25C at 12-bit

    if (htValue != HTU2XD_SHT2X_SI70XX_ERROR)
    {
        return htValue;
    }
    else
    {
        Serial.println(F("<error>"));
        *error = 1;
        return 0;
    }
}

float PG_Sensors::getSoilHumidity(uint8_t *error)
{
    *error = 0;
    uint16_t soil_moisture_out = analogRead(MOISTURE_PIN);

    float val_a = soil_moisture_out - MOISTURE_LOWER_WET;
    float val_b = MOISTURE_UPPER_DRY - MOISTURE_LOWER_WET;

    float percentage_value = (1 - (float)val_a / val_b) * 100;

    return percentage_value;
}

float PG_Sensors::getTemperature(uint8_t *error)
{
    *error = 0;
    float htValue = mt_sensor->readTemperature(); // accuracy +-0.3C in range 0C..60C at 14-bit

    if (htValue != HTU2XD_SHT2X_SI70XX_ERROR) // HTU2XD_SHT2X_SI70XX_ERROR = 255, library returns 255 if error occurs
    {
        return htValue;
    }
    else
    {
        Serial.println(F("<error>"));

        mt_sensor->softReset();
        mt_sensor->setHeater(false);
        mt_sensor->setResolution(HUMD_12BIT_TEMP_14BIT);
        *error = 1;
        return 0;
    }
}

String PG_Sensors::getURLEncodedData()
{

    String url = "";
    uint8_t error_marker = 0;
    float humidity = getHumidity(&error_marker);

    if (error_marker == 0)
    {
        url += "&humidity=" + String(humidity);
    }

    float temperature = getTemperature(&error_marker);

    if (error_marker == 0)
    {
        url += "&temperature=" + String(temperature);
    }

    float humidity_soil = getSoilHumidity(&error_marker);

    if (error_marker == 0)
    {
        url += "&humidity_soil=" + String(humidity_soil);
    }

    return url;
}
