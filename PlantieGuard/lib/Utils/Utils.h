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

#define PING_INTERVAL 5000

String generateUUID();

#endif