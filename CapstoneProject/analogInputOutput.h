/*
 * analogInputOutput.h
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
void WriteMoisture(void);
void supplyWater(void);
int alertWaterIsLow(void);

// Temperature Sensor
extern int ReadTemperatureValue;
void ReadTemperature(void);
void WriteTemperature(void);

// Light Sensor 
extern int ReadLightValue;
void ReadLight(void);
void WriteLight(void);
void learnSupplyWater(void);
#ifdef __cplusplus
} // extern "C"
#endif
#endif /*_ANALOG_INPUT_OUTPUT_*/
