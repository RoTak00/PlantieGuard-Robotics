#ifndef PG_WIFI_H
#define PG_WIFI_H

#include <WiFiS3.h>
#include <PG_LCD.h>
#include <ArduinoJson.h>

class PG_WiFi
{
public:
    PG_WiFi(String ssid, String pass, String uuid, String send_host, PG_LCD *lcd);
    uint8_t init();
    uint8_t connect();
    uint8_t ping();
    uint8_t sendData(String url_encoded_data);
    uint8_t readResponse();

private:
    String _ssid;
    String _pass;
    String _host;
    String _uuid;

    PG_LCD *_lcd;

    WiFiClient _client;

    String _last_body = "";
    JsonDocument _last_json;
    uint8_t _complete_body = false;
    uint8_t _is_body = false;
    uint8_t _reading_chunk_size = false;
    uint16_t _chunk_size = 0;

    String createAck();
    String createSendData(String url_encoded_data);
    void resetResponseData();

public:
    inline uint8_t getStatus() { return WiFi.status(); }
    inline JsonDocument getLastJson() { return _last_json; }
};

#endif
