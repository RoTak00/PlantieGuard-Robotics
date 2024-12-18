#ifndef ACCESS_POINT_H
#define ACCESS_POINT_H

#include <Arduino.h>
#include <PG_LCD.h>
#include <WiFiS3.h>
#include <Utils.h>

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

    uint8_t has_connection_credentials = 0;

private:
    PG_LCD *_lcd;
    String _uuid;

public:
    // Constructor. Initialise Access Point with credentials
    PGAccessPoint(String ssid, String pass, PG_LCD *lcd, String uuid);
    PGAccessPoint();
    uint8_t init();
    uint8_t poll(String *ssid, String *pass);

    // Getter

    inline uint8_t getStatus() { return _status; }
    inline uint8_t getHasConnectionCredentials() { return has_connection_credentials; }

private:
    void _sendHTMLHead();
    void _sendHTMLIndex();
    void _sendHTMLOK();
    void _parseRequest(String *ssid, String *pass);
};

#endif