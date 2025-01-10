#include <AccessPoint.h>
#include <Secrets.h>
#include "WiFiS3.h"

PGAccessPoint::PGAccessPoint(String ssid, String pass, PG_LCD *lcd, String uuid)
{
    this->_ssid = ssid;
    this->_pass = pass;

    this->_status = WL_IDLE_STATUS;

    this->_port = 80;
    this->_lcd = lcd;
    this->_uuid = uuid;

    this->has_connection_credentials = false;
}

PGAccessPoint::PGAccessPoint()
{
    this->_ssid = "PG_Setup";
    this->_pass = "0000";

    this->_status = WL_IDLE_STATUS;

    this->_port = 80;
    this->_lcd = NULL;
    this->_uuid = "";

    this->has_connection_credentials = false;
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

    Serial.print("Creating access point named: ");
    Serial.print(this->_ssid);
    Serial.print("Password ");
    Serial.println(this->_pass);

    this->_lcd->printLong("Connect to " + this->_ssid + " pass " + this->_pass, 0);

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

    this->_lcd->printLong("Go to http://" + ip.toString(), 1);
    return 0;
}

uint8_t PGAccessPoint::poll(String *ssid, String *pass)
{
    this->_client = this->_server.available();

    if (this->_client)
    {
        String currentLine = "";
        this->_last_request = "";
        while (this->_client.connected() && !this->has_connection_credentials)
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
                        this->_sendHTMLIndex();

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

                this->_parseRequest(ssid, pass);
            }
        }
        this->_client.stop();
        Serial.println("Client disconnected.");
        this->_lcd->print("Connected!");
    }

    if (this->has_connection_credentials)
    {

        return 1;
    }
    return 0;
}

void PGAccessPoint::_sendHTMLHead()
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
    this->_client.println("<title>PlantieGuard Setup</title>");
    this->_client.println("<meta charset=\"UTF-8\">");
    this->_client.println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
    this->_client.println("<style>");
    this->_client.println("body {");
    this->_client.println("margin: 1em;");
    this->_client.println("font-family: Arial, Helvetica, sans-serif;");
    this->_client.println("}");
    this->_client.println("html {");
    this->_client.println("font-family: Arial, Helvetica, sans-serif;");
    this->_client.println("}");
    this->_client.println("h1 {");
    this->_client.println("text-align: center;");
    this->_client.println("}");
    this->_client.println("label {");
    this->_client.println("display: block;");
    this->_client.println("padding: 5px 0px;");
    this->_client.println("}");
    this->_client.println("input {");
    this->_client.println("display: block;");
    this->_client.println("width: 100%;");
    this->_client.println("padding: 5px 0px;");
    this->_client.println("}");
    this->_client.println("button {");
    this->_client.println("display: block;");
    this->_client.println("width: 100%;");
    this->_client.println("padding: 5px 0px;");
    this->_client.println("}");
    this->_client.println(".badge {");
    this->_client.println("background-color: #4CAF50;");
    this->_client.println("color: white;");
    this->_client.println("padding: 10px 20px;");
    this->_client.println("text-align: center;");
    this->_client.println("text-decoration: none;");
    this->_client.println("display: inline-block;");
    this->_client.println("font-size: 16px;");
    this->_client.println("margin: 4px 2px;");
    this->_client.println("cursor: pointer;");
    this->_client.println("}");
    this->_client.println("a.button {");
    this->_client.println("background-color: #4CAF50;");
    this->_client.println("color: white;");
    this->_client.println("padding: 10px 20px;");
    this->_client.println("text-align: center;");
    this->_client.println("text-decoration: none;");
    this->_client.println("display: block;");
    this->_client.println("font-size: 16px;");
    this->_client.println("margin: 0 auto;");
    this->_client.println("cursor: pointer;");
    this->_client.println("}");
    this->_client.println("</style>");
    this->_client.println("</head>");
}

void PGAccessPoint::_sendHTMLIndex()
{
    this->_sendHTMLHead();
    this->_client.println("<body>");
    this->_client.println("<h1><span class = 'badge'>PlantieGuard Setup</span> </h1>");
    this->_client.println("<p>You're almost done setting up your PlantieGuard! Write the SSID and the password of your WiFi network below.");
    this->_client.println("PlantieGuard will connect to this network.</p>");
    this->_client.println("<form action=\"/setup\" method=\"get\">");
    this->_client.println("<label for=\"ssid\">SSID:</label>");
    this->_client.println("<input type=\"text\" id=\"ssid\" name=\"ssid\" placeholder=\"SSID\" required>");
    this->_client.println("<br>");
    this->_client.println("<label for=\"pass\">Password:</label>");
    this->_client.println("<input type=\"password\" id=\"pass\" name=\"pass\" placeholder=\"Password\" required>");
    this->_client.println("<br>");
    this->_client.println("<input type=\"submit\" value=\"Submit\">");
    this->_client.println("</form>");
    this->_client.println("</body>");
    this->_client.println("</html>");
}

void PGAccessPoint::_sendHTMLOK()
{
    this->_sendHTMLHead();
    this->_client.println("<body>");
    this->_client.println("<h1><span class = 'badge'>PlantieGuard Setup</span> </h1>");
    this->_client.println("<p>Looking good! PlantieGuard connected</p>");
    this->_client.println("<h2>Next Steps</h2>");
    this->_client.println("<p>PlantieGuard has already begun sending your plantie's data to the server. Now it's time to connect your devices so you can monitor your plants.</p>");
    this->_client.print("<a class = \"button\" href = 'https://");
    this->_client.print(APP_HOST);
    this->_client.print("/account/register/uuid/");
    this->_client.print(_uuid);
    this->_client.print("'>Continue</a>");
    this->_client.println("</body>");
    this->_client.println("</html>");
}

void PGAccessPoint::_parseRequest(String *ssid, String *pass)
{
    if (this->_last_request.indexOf("GET /setup") != -1)
    {
        Serial.println("Found GET /setup");
        String wifi_ssid = this->_last_request.substring(this->_last_request.indexOf("ssid=") + 5, this->_last_request.indexOf("&pass"));
        String wifi_pass = this->_last_request.substring(this->_last_request.indexOf("pass=") + 5, this->_last_request.indexOf(" HTTP"));

        *ssid = wifi_ssid;
        *pass = wifi_pass;

        this->_sendHTMLOK();
        WiFi.end();
        this->has_connection_credentials = 1;

        this->_lcd->print("WiFi received!");
    }
}