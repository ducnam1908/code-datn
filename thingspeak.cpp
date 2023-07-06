#include "thingspeak_diy.h"
#include <WiFi.h>
#include "ThingSpeak.h"

WiFiClient client;

void updateThingSpeak(float humid, float temper, float ph_voltage, float as_val, unsigned long myChannelNumber, const char *myWriteAPIKey) /* Function to post data to Thingspeak */
{
  ThingSpeak.setField(1, temper);
  ThingSpeak.setField(2, humid);
  ThingSpeak.setField(3, ph_voltage);
  ThingSpeak.setField(4, as_val);
  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if (x == 200)
  {
    Serial.println("Channel update successful");
  }
  else
  {
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }
}
void Thingspeak_Begin(void)
{
  ThingSpeak.begin(client);
}
