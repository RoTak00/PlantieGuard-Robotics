
#include <Arduino.h>
#include <PG_LCD.h>

void PG_LCD::print(String text1, String text2)
{
    reset();

    this->_lcd->clear();
    this->_lcd->setCursor(0, 0);
    this->_lcd->print(text1.substring(0, SCREEN_W));
    this->_lcd->setCursor(0, 1);
    this->_lcd->print(text2.substring(0, SCREEN_W));
}

void PG_LCD::print(String text)
{
    reset(1);
    this->_lcd->setCursor(0, 0);
    // clear this line only first
    this->_lcd->print("                ");
    this->_lcd->setCursor(0, 0);
    this->_lcd->print(text.substring(0, SCREEN_W));
}

void PG_LCD::print(int _, String text)
{
    reset(2);
    this->_lcd->setCursor(0, 1);
    // clear this line only first
    this->_lcd->print("                ");
    this->_lcd->setCursor(0, 1);
    this->_lcd->print(text.substring(0, SCREEN_W));
}

void PG_LCD::print_no_reset(String text)
{
    this->_lcd->setCursor(0, 0);
    // clear this line only first
    this->_lcd->print("                ");
    this->_lcd->setCursor(0, 0);
    this->_lcd->print(text.substring(0, SCREEN_W));
}

void PG_LCD::print_no_reset(int _, String text)
{
    this->_lcd->setCursor(0, 1);
    // clear this line only first
    this->_lcd->print("                ");
    this->_lcd->setCursor(0, 1);
    this->_lcd->print(text.substring(0, SCREEN_W));
}

void PG_LCD::printLong(String text, uint8_t position)
{
    Serial.print("print Long ");
    Serial.print(text.length());
    Serial.println(text);
    if (text.length() <= SCREEN_W)
    {
        if (position == 0)
        {
            this->print(text);
        }
        else
        {
            this->print(0, text);
        }
        return;
    }

    Serial.println("setting buffers");
    Serial.println(text);

    if (position == 0)
    {
        this->_current_text_0 = String(text);
        this->_current_position_0 = -4;
    }

    if (position == 1)
    {
        this->_current_text_1 = text;
        this->_current_position_1 = -4;
    }

    return;
}

void PG_LCD::update()
{
    if (millis() - _last_update > UPDATE_DELAY)
    {
        if (_current_text_0.length())
        {
            int16_t true_pos = this->_current_position_0;

            if (true_pos < 0)
            {
                true_pos = 0;
            }

            if (_current_text_0.length() - _current_position_0 < SCREEN_W)
            {
                true_pos = _current_text_0.length() - SCREEN_W;
            }

            this->print_no_reset(this->_current_text_0.substring(true_pos, SCREEN_W + true_pos));
            if (_current_text_0.length() - _current_position_0 > SCREEN_W - EXTRA_WAIT)
            {
                _current_position_0++;
            }
            else
            {
                _current_position_0 = -EXTRA_WAIT;
            }
        }

        if (_current_text_1.length())
        {
            int16_t true_pos = this->_current_position_1;
            if (true_pos < 0)
            {
                true_pos = 0;
            }

            if (_current_text_1.length() - _current_position_1 < SCREEN_W)
            {
                true_pos = _current_text_1.length() - SCREEN_W;
            }

            this->print_no_reset(0, this->_current_text_1.substring(true_pos, SCREEN_W + true_pos));
            if (_current_text_1.length() - _current_position_1 > SCREEN_W - EXTRA_WAIT)
            {
                _current_position_1++;
            }
            else
            {
                _current_position_1 = -EXTRA_WAIT;
            }
        }

        _last_update = millis();
    }
}

void PG_LCD::reset()
{
    reset(3);
}

void PG_LCD::reset(uint8_t which)
{
    if (which & 1)
    {
        _current_text_0 = "";
        _current_position_0 = 0;
    }

    if (which & 2)
    {
        _current_text_1 = "";
        _current_position_1 = 0;
    }
}