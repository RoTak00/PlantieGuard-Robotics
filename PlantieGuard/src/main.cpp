#include <Arduino.h>
#include <AccessPoint.h>
#include <PG_LCD.h>
#include <Serial.h>
#include <Utils.h>

PG_LCD *lcd = new PG_LCD();
PGAccessPoint *access_point = NULL;

String WiFi_SSID = "", WiFi_PASS = "";

PlantieGuardStatus status = INIT_ACESS_POINT;

void setup()
{
  Serial.begin(9600);
  while (!Serial)
    ;

  Serial.println("Hello world!");
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

      Serial.print("SSID: ");
      Serial.println(WiFi_SSID);
      Serial.print("PASS: ");
      Serial.println(WiFi_PASS);
    }

    break;
  case CONNECTING_WIFI:
    Serial.println("Connecting to WiFi");
    delay(1000);
    break;
  }
}
