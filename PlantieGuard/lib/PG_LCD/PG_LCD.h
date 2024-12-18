#ifndef PG_LCD_H
#define PG_LCD_H

#include <Arduino.h>
#include <LiquidCrystal.h>

class PG_LCD
{
private:
    uint8_t _status;
    LiquidCrystal *_lcd;

    const uint8_t SCREEN_W = 16;
    const uint8_t RS_PIN = 12;
    const uint8_t E_PIN = 11;
    const uint8_t D4_PIN = 5;
    const uint8_t D5_PIN = 4;
    const uint8_t D6_PIN = 3;
    const uint8_t D7_PIN = 2;
    const uint16_t UPDATE_DELAY = 750;
    const uint8_t EXTRA_WAIT = 3;

    String _current_text_0 = "";
    String _current_text_1 = "";
    uint64_t _last_update = 0;
    int16_t _current_position_0 = -4;
    int16_t _current_position_1 = -4;

public:
    // TODO: Implement LCD class
    PG_LCD()
    {
        this->_lcd = new LiquidCrystal(RS_PIN, E_PIN, D4_PIN, D5_PIN, D6_PIN, D7_PIN);

        this->_lcd->begin(SCREEN_W, 2);
    }
    void print(String text1, String text2);

    void print(String text);

    void print(int _, String text);

    void print_no_reset(String text);

    void print_no_reset(int _, String text);

    void printLong(String text, uint8_t position);

    void update();

    void reset(uint8_t which);

    void reset();
};

#endif