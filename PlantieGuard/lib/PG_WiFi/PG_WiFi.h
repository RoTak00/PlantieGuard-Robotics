#ifndef PG_WIFI_H
#define PG_WIFI_H

#include <WiFiS3.h>
#include <PG_LCD.h>

class PG_WiFi
{
public:
    PG_WiFi(String ssid, String pass, String send_host, PG_LCD *lcd);
    uint8_t init();
    uint8_t connect();
    uint8_t ping();
    void readResponse();

private:
    String _ssid;
    String _pass;
    String _host;

    PG_LCD *_lcd;

    WiFiClient _client;

    uint64_t _last_ping = 0;

    String createAck();

public:
    inline uint8_t getStatus() { return WiFi.status(); }
};

#endif
