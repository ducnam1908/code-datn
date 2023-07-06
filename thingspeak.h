#ifndef THINGSPEAK_DIY_H
#define THINGSPEAK_DIY_H

void Thingspeak_Begin(void);
void updateThingSpeak(float humid, float temper, float ph_voltage, float as_val, unsigned long myChannelNumber, const char *myWriteAPIKey);

#endif
