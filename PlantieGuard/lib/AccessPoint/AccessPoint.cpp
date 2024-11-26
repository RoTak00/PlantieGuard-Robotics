#include <AccessPoint.h>
#include "WiFiS3.h"

PGAccessPoint::PGAccessPoint(String ssid, String pass, PG_LCD *lcd)
{
    this->_ssid = ssid;
    this->_pass = pass;

    this->_status = WL_IDLE_STATUS;

    this->_port = 80;
    this->_lcd = lcd;
}

PGAccessPoint::PGAccessPoint()
{
    this->_ssid = "PG_Setup";
    this->_pass = "0000";

    this->_status = WL_IDLE_STATUS;

    this->_port = 80;
}

uint8_t PGAccessPoint::init()
{

    if (WiFi.status() == WL_NO_MODULE)
    {
        // this->_lcd->print("Communication with WiFi module failed!");
        Serial.println("Communication with WiFi module failed!");
        return 1;
    }

    String fv = WiFi.firmwareVersion();

    if (fv < WIFI_FIRMWARE_LATEST_VERSION)
    {
        // this->_lcd->print("WiFi firmware outdated.");
        Serial.println("WiFi firmware outdated.");
    }

    // this->_lcd->print("Creating access point named: ");
    // this->_lcd->print(this->_ssid);
    // this->_lcd->print("Pass");
    // this->_lcd->print(this->_pass);
    Serial.print("Creating access point named: ");
    Serial.print(this->_ssid);
    Serial.print("Password ");
    Serial.println(this->_pass);

    this->_status = WiFi.beginAP(this->_ssid.c_str(), this->_pass.c_str());
    if (this->_status != WL_AP_LISTENING)
    {
        // this->_lcd->print("Creating access point failed");
        Serial.println("Creating access point failed");
        this->_status = 255;
        return 1;
    }

    this->_server.begin(this->_port);

    IPAddress ip = WiFi.localIP();
    // this->_lcd->print("Connect to http://");
    // this->_lcd->print(ip);
    Serial.print("Connect to http://");
    Serial.println(ip);
    return 0;
}

uint8_t PGAccessPoint::poll()
{
    this->_client = this->_server.available();

    if (this->_client)
    {
        String currentLine = "";
        this->_last_request = "";
        while (this->_client.connected())
        {
            if (this->_client.available())
            {
                char c = this->_client.read();

                if (c == '\n')
                { // if the byte is a newline character

                    // if the current line is blank, you got two newline characters in a row.
                    // that's the end of the client HTTP request, so send a response:
                    if (currentLine.length() == 0)
                    {
                        this->_sendHTML();

                        break;
                    }
                    else
                    {
                        this->_last_request += currentLine;
                        currentLine = "";
                    }
                }
                else if (c != '\r')
                {                     // if you got anything else but a carriage return character,
                    currentLine += c; // add it to the end of the currentLine
                }

                this->_parseRequest();
            }
        }
        this->_client.stop();
        Serial.println("Client disconnected.");
        Serial.println(this->_last_request);
    }
}

void PGAccessPoint::_sendHTML()
{
    this->_client.println("HTTP/1.1 200 OK");
    this->_client.println("Server: Arduino/ESP32");
    this->_client.println("Content-Type: text/html; charset=UTF-8");
    this->_client.println("Connection: close");
    this->_client.println("Cache-Control: no-cache");
    this->_client.println("Expires: 0");
    this->_client.println("Accept-Ranges: bytes");
    this->_client.println();

    this->_client.println("<!DOCTYPE html>");
    this->_client.println("<html>");
    this->_client.println("<head>");
    this->_client.println("<title>PG Setup</title>");
    this->_client.println("<meta charset=\"UTF-8\">");
    this->_client.println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
    this->_client.println("</head>");
    this->_client.println("<body>");
    this->_client.println("<h1>PG Setup</h1>");
    this->_client.println("<a href=\"/B\">Button</a>");
    this->_client.println("</body>");
    this->_client.println("</html>");
}

void PGAccessPoint::_parseRequest()
{
}
