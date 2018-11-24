/*
 * sensors.h
 *
 *  Created on: Nov 15, 2018
 *      Author: Jin Taek Lee, Thishone Wijayakumar, Ajo Cherian Thomas
 */
#ifndef _ANALOG_INPUT_OUTPUT_
#define _ANALOG_INPUT_OUTPUT_
#ifdef __cplusplus
extern "C" {
#endif

// Soil Moisture Sensor
void setMaxMoistureValue(int max);
void setMinMoistureValue(int min);

int ReadMoisture(void);
void supplyWater(void);

// Temperature Sensor
void ReadTemperature(void);
void DHT11_HumiditySensor(void);

// Light Sensor 
void ReadLight(void);

void ReadOverflow(void);
void learnSupplyWater(void);
#ifdef __cplusplus
} // extern "C"
#endif
#endif /*_ANALOG_INPUT_OUTPUT_*/
