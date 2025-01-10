#include <Utils.h>
#include <Serial.h>

String generateUUID()
{
    String uuid = "";
    const char hexChars[] = "0123456789abcdef";

    for (int i = 0; i < 36; i++)
    {
        if (i == 8 || i == 13 || i == 18 || i == 23)
        {
            uuid += "-";
        }
        else if (i == 14)
        {
            uuid += "4"; // UUID version 4
        }
        else if (i == 19)
        {
            // UUID variant (8, 9, a, or b)
            uuid += hexChars[(random(8, 12))];
        }
        else
        {
            uuid += hexChars[random(0, 16)];
        }
    }

    return uuid;
}

uint64_t last_reset_button_debounce_time = 0;
uint8_t last_reset_button_state = 0;
uint8_t current_reset_button_state = 0;

void initResetButton()
{
    pinMode(RESET_BUTTON_PIN, INPUT_PULLUP);
}

uint8_t checkResetButton()
{
    uint8_t reading = digitalRead(RESET_BUTTON_PIN);

    if (current_reset_button_state == HIGH)
    {
        current_reset_button_state = LOW;
    }

    if (reading != last_reset_button_state)
    {
        last_reset_button_debounce_time = millis();
    }

    if ((millis() - last_reset_button_debounce_time) > RESET_BUTTON_DELAY)
    {

        if (reading != current_reset_button_state)
        {
            current_reset_button_state = reading;
        }

        if (current_reset_button_state == HIGH)
        {
            last_reset_button_debounce_time = millis();
        }
    }

    last_reset_button_state = reading;

    return current_reset_button_state;
}