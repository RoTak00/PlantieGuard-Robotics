#ifndef PG_LCD_H
#define PG_LCD_H

#include <Arduino.h>
#include <Serial.h>

class PG_LCD
{
private:
    uint8_t _status;

public:
    // TODO: Implement LCD class
    PG_LCD() { this->_status = 0; }
    void print(String text)
    {
        Serial.println(text);
        if (this->_status == 0)
            ;
    };

    void print(uint8_t text) { this->print(String(text)); };
};

#endif