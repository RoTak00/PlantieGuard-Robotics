#ifndef EEPROM_H
#define EEPROM_H

class PG_EEPROM
{
public:
    PG_EEPROM();
    uint8_t writeCredentials(String ssid, String pass);

    uint8_t getCredentials(String &ssid, String &pass);

    uint8_t getUUID(String &uuid);

    uint8_t writeUUID(String uuid);

private:
    const uint8_t CREDENTIALS_START = 40;
    const uint8_t UUID_LENGTH = 36;
};

#endif