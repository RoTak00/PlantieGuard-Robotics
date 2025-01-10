#ifndef UTILS_H
#define UTILS_H

#include <Arduino.h>

enum PlantieGuardStatus
{
    INIT_ACESS_POINT,
    POLLING_ACESS_POINT,
    CONNECTING_WIFI,
    LOADING_WIFI,
    CONNECTED_ACTIVE
};

#define PING_INTERVAL 30000

String generateUUID();

#define RESET_BUTTON_PIN 9
#define RESET_BUTTON_DELAY 5000
void initResetButton();

extern uint64_t last_reset_button_debounce_time;
extern uint8_t last_reset_button_state;
extern uint8_t current_reset_button_state;

uint8_t checkResetButton();

#endif