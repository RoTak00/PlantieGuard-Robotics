#include <PG_WiFi.h>
#include <Utils.h>
#include <ArduinoJson.h>

PG_WiFi::PG_WiFi(String ssid, String pass, String uuid, String host, PG_LCD *lcd)
{
    _ssid = ssid;
    _pass = pass;
    _host = host;
    _uuid = uuid;

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
    Serial.println("Ping");
    if (_client.connected())
    {
        _client.print(createAck());
        resetResponseData();
        return 1;
    }
    else
    {
        return 2;
    }

    return 0;
}

uint8_t PG_WiFi::sendData(String url_encoded_data)
{

    if (_client.connected())
    {
        Serial.println("can send");
        _client.print(createSendData(url_encoded_data));
        resetResponseData();
        return 1;
    }
    else
    {
        return 2;
    }

    return 0;
}

uint8_t PG_WiFi::readResponse()
{

    if (_client.available())
    {
        if (!_complete_body)
        {
            String line = _client.readStringUntil('\n');
            line.trim();

            if (line.isEmpty() && !_is_body)
            {
                // End of headers; start of body
                _is_body = true;
            }
            else if (_is_body)
            {
                // Handle chunked transfer encoding
                if (!_reading_chunk_size)
                {
                    // Read the chunk size (in hexadecimal)
                    _chunk_size = strtol(line.c_str(), NULL, 16);

                    // If the chunk size is 0, it's the end of the body
                    if (_chunk_size == 0)
                    {
                        _is_body = false;      // Stop reading
                        _complete_body = true; // Mark response as complete

                        if (deserializeJson(_last_json, _last_body) == DeserializationError::Ok)
                        {
                            resetResponseData();
                            return 1; // Successfully parsed JSON
                        }
                        else
                        {
                            Serial.println("Error parsing JSON");
                            return 2;
                        }
                    }
                    else
                    {
                        _reading_chunk_size = true; // Now read the chunk data
                    }
                }
                else
                {
                    if (line.length() <= _chunk_size)
                    {
                        _last_body += line;
                        _chunk_size -= line.length();

                        if (_chunk_size <= 0)
                        {
                            _reading_chunk_size = false;
                        }
                    }
                    else
                    {
                        Serial.println("chunk error");
                    }
                }
            }
            else if (!_is_body)
            {
                // check if line has HTTP/1.1, and if it does, check that it must have 200
                if (line.indexOf("HTTP/1.1") != -1)
                {
                    if (line.indexOf("200") == -1)
                    {
                        Serial.println("Error: " + line);
                    }
                }
            }
        }
    }

    return 0;
}

String PG_WiFi::createAck()
{
    String ack = "GET /?action=ack&token=" + _uuid + " HTTP/1.1\r\n";
    ack += "Host: " + _host + "\r\n";
    ack += "Connection: close\r\n\r\n";

    Serial.println(ack);
    return ack;
}

String PG_WiFi::createSendData(String url_encoded_data)
{
    String ack = "GET /?action=data&token = " + _uuid;
    ack += url_encoded_data;
    ack += " HTTP / 1.1\r\n ";
    ack += "Host: " + _host + "\r\n";
    ack += "Connection: close\r\n\r\n";
    return ack;
}

void PG_WiFi::resetResponseData()
{
    _complete_body = false;
    _is_body = false;
    _last_body = "";
    _reading_chunk_size = false;
    _chunk_size = 0;

    return;
}