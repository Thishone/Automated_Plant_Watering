#ifndef _ANALOG_INPUT_OUTPUT_
#define _ANALOG_INPUT_OUTPUT_
#ifdef __cplusplus
extern "C" {
#endif

// Soil Moisture Sensor
extern int ReadMoistureValue;
int ReadMoisture(void);
void WriteMoisture(void);
void supplyWater(void);
extern unsigned int  max_moisture;
extern unsigned int  min_moisture;
// Temperature Sensor
extern int ReadTemperatureValue;
void ReadTemperature(void);
void WriteTemperature(void);

// Light Sensor 
extern int ReadLightValue;
void ReadLight(void);
void WriteLight(void);

#ifdef __cplusplus
} // extern "C"
#endif
#endif /*_ANALOG_INPUT_OUTPUT_*/
