#include <Arduino.h>
#include <AccessPoint.h>
#include <PG_LCD.h>
#include <Serial.h>
#include <Utils.h>
#include <Secrets.h>
#include <PG_WiFi.h>

PG_LCD *lcd = new PG_LCD();
PGAccessPoint *access_point = NULL;

PG_WiFi *wifi = NULL;

String WiFi_SSID = "", WiFi_PASS = "";

PlantieGuardStatus status = INIT_ACESS_POINT;

void setup()
{
  Serial.begin(9600);
  while (!Serial)
    ;

  access_point = new PGAccessPoint("PG_Setup_1.0", "12345678", lcd);
}

void loop()
{
  switch (status)
  {
  case INIT_ACESS_POINT:
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
    wifi = new PG_WiFi(WiFi_SSID, WiFi_PASS, SEND_HOST, lcd);
    wifi->init();

    status = LOADING_WIFI;

    break;

  case LOADING_WIFI:

    if (wifi->getStatus() == WL_CONNECTED)
    {
      Serial.println("Wifi connected");
      if (wifi->connect())
      {
        Serial.println("Connected to server");
        status = CONNECTED_ACTIVE;
      }
    }
    else if (wifi->getStatus() == WL_IDLE_STATUS)
    {
      status = INIT_ACESS_POINT;
    }

    delay(1000);
    break;

  case CONNECTED_ACTIVE:

    if (wifi->ping() == 2)
    {
      status = LOADING_WIFI;
    }

    wifi->readResponse();

    break;
  }
}
