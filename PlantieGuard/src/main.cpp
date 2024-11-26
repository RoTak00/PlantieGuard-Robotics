#include <Arduino.h>
#include <AccessPoint.h>
#include <PG_LCD.h>
#include <Serial.h>

PG_LCD *lcd = new PG_LCD();
PGAccessPoint *access_point = NULL;

void setup()
{
  Serial.begin(115200);
  while (!Serial)
    ;

  Serial.println("Hello world!");
  access_point = new PGAccessPoint("PG_Setup_1.0", "12345678", lcd);
}

void loop()
{
  if (access_point->getStatus() == 0)
  {
    access_point->init();
  }
  else
  {
    access_point->poll();
  }
}
