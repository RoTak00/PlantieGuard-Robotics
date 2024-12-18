#include <Arduino.h>
#include <AccessPoint.h>
#include <PG_LCD.h>
#include <Serial.h>
#include <Utils.h>
#include <Secrets.h>
#include <PG_WiFi.h>
#include <PG_EEPROM.h>
#include <PG_Sensors.h>

PG_LCD *lcd = NULL;
PGAccessPoint *access_point = NULL;

PG_WiFi *wifi = NULL;

PG_EEPROM *rom = NULL;

PG_Sensors *sensors = NULL;

String WiFi_SSID = "", WiFi_PASS = "", WiFi_UUID = "";

PlantieGuardStatus status = INIT_ACESS_POINT;

uint64_t last_ping = 0;

void setup()
{
  Serial.begin(9600);
  while (!Serial)
    ;

  rom = new PG_EEPROM();
  sensors = new PG_Sensors();

  if (!rom->getUUID(WiFi_UUID))
  {
    WiFi_UUID = generateUUID();
    rom->writeUUID(WiFi_UUID);
  }

  Serial.println("UUID: " + WiFi_UUID);

  // if (rom->getCredentials(WiFi_SSID, WiFi_PASS))
  // {
  //   Serial.println("Credentials found");
  //   status = CONNECTING_WIFI;
  // }
  lcd = new PG_LCD();

  lcd->print("PlantieGuard", "Initializing");
}

void loop()
{
  switch (status)
  {
  case INIT_ACESS_POINT:

    access_point = new PGAccessPoint("PG_Setup_1.0", "12345678", lcd, WiFi_UUID);
    access_point->init();

    if (access_point->getStatus() != 0)
    {
      status = POLLING_ACESS_POINT;
    }
    break;
  case POLLING_ACESS_POINT:
    access_point->poll(&WiFi_SSID, &WiFi_PASS);

    if (access_point->getHasConnectionCredentials())
    {
      status = CONNECTING_WIFI;
    }

    break;
  case CONNECTING_WIFI:
    wifi = new PG_WiFi(WiFi_SSID, WiFi_PASS, WiFi_UUID, SEND_HOST, lcd);
    wifi->init();

    status = LOADING_WIFI;

    break;

  case LOADING_WIFI:

    if (wifi->getStatus() == WL_CONNECTED)
    {
      rom->writeCredentials(WiFi_SSID, WiFi_PASS);

      if (millis() - last_ping > 10000 || last_ping == false)
      {
        if (wifi->connect())
        {
          Serial.println("Connected to server");
          lcd->print("PlantieGuard", "Connected");
          if (wifi->ping() == 1)
          {
            Serial.println("Sent ack successfully");
            last_ping = millis();
          }
        }
      }

      if (wifi->readResponse() == 1)
      {
        JsonDocument json = wifi->getLastJson();

        if (json.containsKey("version"))
        {
          String versionValue = json["version"].as<String>();
          Serial.println("version " + versionValue);
        }
        if (json.containsKey("ack"))
        {
          String ackValue = json["ack"].as<String>();
          Serial.println("ack " + ackValue);

          status = CONNECTED_ACTIVE;
        }
      }
    }
    else if (wifi->getStatus() == WL_IDLE_STATUS)
    {
      status = INIT_ACESS_POINT;
    }

    break;

  case CONNECTED_ACTIVE:

    if (millis() - last_ping > 10000)
    {
      Serial.println("Reading sensors");

      String sensors_url = sensors->getURLEncodedData();

      Serial.println("In connected active");
      if (wifi->connect())
      {
        Serial.println("Connected to server (ca)");
        lcd->print("PlantieGuard", "Sending data");
        if (wifi->sendData(sensors_url) == 2)
        {
          status = LOADING_WIFI;
        }

        last_ping = millis();
      }
    }

    if (wifi->readResponse())
    {
      JsonDocument json = wifi->getLastJson();

      String ver = json['version'];
      Serial.println(ver);

      lcd->print("PlantieGuard", "OK");
    }

    break;
  }

  lcd->update();
}
