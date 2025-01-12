#include <EEPROM.h>
#include <PG_EEPROM.h>
#include <Serial.h>

PG_EEPROM::PG_EEPROM() {}

uint8_t PG_EEPROM::getUUID(String &uuid)
{
    int i = 0;
    char c = 0;

    if ((c = EEPROM.read(i)) != 'u')
    {
        return 0;
    }
    i++;
    if ((c = EEPROM.read(i)) != 0)
    {
        return 0;
    }
    i++;

    uuid = "";
    while ((c = EEPROM.read(i)) != 0)
    {
        uuid += c;
        i++;
    }

    if (uuid.length() != UUID_LENGTH)
    {
        return 0;
    }

    if ((c = EEPROM.read(i)) != 0)
    {
        return 0;
    }
    i++;

    if ((c = EEPROM.read(i)) != 0)
    {
        return 0;
    }
    i++;

    return 1;
}

uint8_t PG_EEPROM::writeUUID(String uuid)
{
    if (uuid.length() != UUID_LENGTH)
    {
        return 0;
    }

    int i = 0;
    EEPROM.write(i, 'u');
    i++;
    EEPROM.write(i, 0);
    i++;
    for (int j = 0; j < uuid.length(); j++)
    {
        EEPROM.write(i, uuid[j]);
        i++;
    }
    EEPROM.write(i, 0);
    i++;
    EEPROM.write(i, 0);
    i++;
    return 1;
}

uint8_t PG_EEPROM::writeCredentials(String ssid, String pass)
{
    // i starts after the uuid
    int i = CREDENTIALS_START;
    EEPROM.write(i, 's');
    i++;
    EEPROM.write(i, 0);
    i++;
    for (int j = 0; j < ssid.length(); j++)
    {
        EEPROM.write(i, ssid[j]);
        i++;
    }
    EEPROM.write(i, 0);
    i++;
    EEPROM.write(i, 0);
    i++;
    EEPROM.write(i, 'p');
    i++;
    EEPROM.write(i, 0);
    i++;
    for (int j = 0; j < pass.length(); j++)
    {
        EEPROM.write(i, pass[j]);
        i++;
    }
    EEPROM.write(i, 0);
    i++;
    EEPROM.write(i, 0);
    i++;
    return 1;
}

uint8_t PG_EEPROM::getCredentials(String &ssid, String &pass)
{
    int i = CREDENTIALS_START;
    char c = 0;

    if ((c = EEPROM.read(i)) != 's')
    {
        return 0;
    }
    i++;
    if ((c = EEPROM.read(i)) != 0)
    {
        return 0;
    }
    i++;

    ssid = "";
    while ((c = EEPROM.read(i)) != 0)
    {
        ssid += c;
        i++;
    }
    i++;

    if ((c = EEPROM.read(i)) != 0)
    {
        return 0;
    }
    i++;

    if ((c = EEPROM.read(i)) != 'p')
    {
        return 0;
    }
    i++;
    if ((c = EEPROM.read(i)) != 0)
    {
        return 0;
    }
    i++;
    pass = "";
    while ((c = EEPROM.read(i)) != 0)
    {
        pass += c;
        i++;
    }
    return 1;
}

void PG_EEPROM::clear()
{
    // EEPROM is big, so we clear up to 512
    Serial.println("Clearing EEPROM");
    for (int i = 0; i < (1 << 9); i++)
    {

        if (i % 50 == 0)
        {
            Serial.println(i);
        }
        EEPROM.write(i, 0);
    }
}