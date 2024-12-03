#include <PG_WiFi.h>
PG_WiFi::PG_WiFi(String ssid, String pass, String host, PG_LCD *lcd)
{
    _ssid = ssid;
    _pass = pass;
    _host = host;

    _lcd = lcd;
}

uint8_t PG_WiFi::init()
{
    return WiFi.begin(_ssid.c_str(), _pass.c_str());
}

uint8_t PG_WiFi::connect()
{
    if (_client.connect(_host.c_str(), 80))
    {
        Serial.println("Connected to server");
        _last_ping = millis();
        return 1;
    }
    else
    {
        Serial.println("Connection to server failed");
    }

    return 0;
}

uint8_t PG_WiFi::ping()
{
    if (millis() - _last_ping > 5000)
    {
        Serial.println("Ping");
        _last_ping = millis();
        if (_client.connected())
        {
            _client.print(createAck());
            return 1;
        }
        else
        {
            return 2;
        }
    }
    return 0;
}

void PG_WiFi::readResponse()
{
    if (_client.available())
    {
        String line = _client.readStringUntil('\n');
        Serial.println(line);
    }
}

String PG_WiFi::createAck()
{
    String ack = "GET /ack HTTP/1.1\r\n";
    ack += "Host: " + _host + "\r\n";
    ack += "Connection: close\r\n\r\n";
    return ack;
}