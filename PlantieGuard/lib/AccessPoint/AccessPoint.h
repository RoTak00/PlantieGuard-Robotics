#ifndef ACCESS_POINT_H
#define ACCESS_POINT_H

#include <Arduino.h>
#include <PG_LCD.h>
#include <WiFiS3.h>

class PGAccessPoint
{
private:
    String _ssid;
    String _pass;

    uint8_t _status;

    WiFiServer _server;
    WiFiClient _client;

    uint8_t _port;

    String _last_request = "";

private:
    PG_LCD *_lcd;

public:
    // Constructor. Initialise Access Point with credentials
    PGAccessPoint(String ssid, String pass, PG_LCD *lcd);
    PGAccessPoint();
    uint8_t init();
    uint8_t poll();

    // Getter

    inline uint8_t getStatus() { return _status; }

private:
    void _sendHTML();
    void _parseRequest();
};

#endif