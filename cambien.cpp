#include <DHT.h>
#include "sensor.h"

DHT dht(DHTPIN, DHTTYPE);
void Sensor_Init(void)
{
    Serial.println("DHT11 Thuy Canh!");
    dht.begin();
    pinMode(DHTPIN, INPUT);
    pinMode(ASPIN, INPUT);
    pinMode(PHPIN, INPUT);


//    pinMode(APP_LAMP, OUTPUT);
     pinMode(APP_LAMP2, OUTPUT);
    pinMode(PUMP_HUM, OUTPUT);
    pinMode(FAN_HUM, OUTPUT);
    pinMode(FAN_TEMP, OUTPUT);
    pinMode(LIGH_TEMP, OUTPUT);
    pinMode(PUMP_AXIT, OUTPUT);
    pinMode(PUMP_BAZO, OUTPUT);

    digitalWrite(PUMP_HUM, LOW);
    digitalWrite(FAN_HUM, LOW);
    digitalWrite(FAN_TEMP, LOW);
    digitalWrite(LIGH_TEMP, LOW);
    digitalWrite(PUMP_AXIT, LOW);
    digitalWrite(PUMP_BAZO, LOW);
//    digitalWrite(APP_LAMP, LOW);
     digitalWrite(APP_LAMP2, LOW);
}
void Sensor_Read(float *humid, float *temper, float *ph_val, float *as_val)
{
    *ph_val = 0;
    *as_val = 0;
    *humid = 0;
    *temper = 0;
    *humid = dht.readHumidity();
    *temper = dht.readTemperature();
    if (isnan(*humid) || isnan(*temper)) 
    {
        *humid = 0;
        *temper = 0;
    }

    for(int i=0; i<10; i++)
    {
        *ph_val += analogRead(PHPIN);
    }
    for(int i=0; i<10; i++)
    {
        *as_val += analogRead(ASPIN);
    }
    *ph_val = *ph_val/10;
    *as_val = *as_val/10;
}
/*
* Exchange to voltage value and display into LCD
*/
void Sensor_Exchange_Voltage(float *ph_val, float *as_val, float *ph_voltage, float *as_voltage)
{
  if(*ph_val <= 3000)
  {
    *ph_voltage = 7 + (3000 - *ph_val)/100;
    if(*ph_voltage > 10)
    {
      *ph_voltage = 10;
    }
  }
  else
  {
    *ph_voltage = 7 - (*ph_val - 3000)/100;
    if(*ph_voltage < 3)
    {
      *ph_voltage = 3;
    }
  }
  *as_voltage = (*as_val/4095)*3.3;
}

void Check_Value_And_Alarm(float humid, float temper, float ph_voltage)
{
  /* Humid check */
  if(humid <= 70)
  {
    digitalWrite(FAN_HUM, LOW);
    digitalWrite(PUMP_HUM, HIGH);
  }
  else if (humid >= 88)
  {
    digitalWrite(PUMP_HUM, LOW);
    digitalWrite(FAN_HUM, HIGH);
  }
  else
  {
    digitalWrite(FAN_HUM, LOW);
    digitalWrite(PUMP_HUM, LOW);
  }

  /* Temper check */
  if(temper <= 28)
  {
    digitalWrite(FAN_TEMP, LOW);
    digitalWrite(LIGH_TEMP, HIGH);
  }
  else if (temper >= 35)
  {
    digitalWrite(LIGH_TEMP, LOW);
    digitalWrite(FAN_TEMP, HIGH);
  }
  else
  {
    digitalWrite(FAN_TEMP, LOW);
    digitalWrite(LIGH_TEMP, LOW);
  }

//  /* PH check */
  if(ph_voltage <= 2800)
  {
    digitalWrite(PUMP_BAZO, HIGH);
    digitalWrite(PUMP_AXIT, LOW);
  }
  else if (ph_voltage >= 3500)
  {
    digitalWrite(PUMP_BAZO, LOW);
    digitalWrite(PUMP_AXIT, HIGH);
  }
  else
  {
    digitalWrite(PUMP_AXIT, LOW);
    digitalWrite(PUMP_BAZO, LOW);
  }
}

void Control_Device(char *str)
{
  if(strstr(str,"batbazo") != NULL)
  {
    digitalWrite(PUMP_BAZO, HIGH);
  }
  else if(strstr(str,"tatbazo") != NULL)
  {
    digitalWrite(PUMP_BAZO, LOW);
  }
  else if(strstr(str,"bataxit") != NULL)
  {
    digitalWrite(PUMP_AXIT, HIGH);
  }
  else if(strstr(str,"tataxit") != NULL)
  {
    digitalWrite(PUMP_AXIT, LOW);
  }


  else if(strstr(str,"hilubat") != NULL)
  {
    Serial.println("bat phun suong");
    digitalWrite(PUMP_HUM, HIGH);
  }
  else if(strstr(str,"hilutat") != NULL)
  {
    Serial.println("tat phun suong");
    digitalWrite(PUMP_HUM, LOW);
  }
  else if(strstr(str,"bathut") != NULL)
  {
    digitalWrite(FAN_HUM, HIGH);
  }
  else if(strstr(str,"tathut") != NULL)
  {
    digitalWrite(FAN_HUM, LOW);
  }


  else if(strstr(str,"batmat") != NULL)
  {
    digitalWrite(FAN_TEMP, HIGH);
  }
  else if(strstr(str,"tatmat") != NULL)
  {
    digitalWrite(FAN_TEMP, LOW);
  }
  else if(strstr(str,"batsuoi") != NULL)
  {
    digitalWrite(LIGH_TEMP, HIGH);
  }
  else if(strstr(str,"tatsuoi") != NULL)
  {
    digitalWrite(LIGH_TEMP, LOW);
  }
}
