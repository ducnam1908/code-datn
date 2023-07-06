#ifndef SENSOR_H
#define SENSOR_H

#define DHTPIN 15
#define ASPIN 36
#define PHPIN 39
#define DHTTYPE DHT11  

//#define APP_LAMP 23
#define APP_LAMP2 5
#define FAN_HUM 2
#define PUMP_HUM 33
#define FAN_TEMP 4
#define LIGH_TEMP 18
#define PUMP_AXIT 32
#define PUMP_BAZO 23

void Sensor_Init(void);
void Sensor_Read(float *humid, float *temper, float *ph_val, float *as_val);
void Sensor_Exchange_Voltage(float *ph_val, float *as_val, float *ph_voltage, float *as_voltage);
void Check_Value_And_Alarm(float humid, float temper, float ph_voltage);
void Control_Device(char *str);

#endif
